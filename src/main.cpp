#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DHT.h>
#include <Ticker.h>
#include <Security.h>

#define DHTPIN 5
#define DHTTYPE DHT22

Security security;
ESP8266WebServer server(80);
DHT dht(DHTPIN, DHTTYPE);
Ticker ticker;

bool wait = false;

void waiting() {
  if (wait) {
    wait = false;
    ticker.detach();
    Serial.println("ready for read!");
  } else {
    wait = true;
    Serial.println("Wating to read...");
    ticker.attach(2, waiting);
  }
}

void handle() {
  if (!wait) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    waiting();

    if (isnan(h) || isnan(t)) {
      server.send(200, "text/plain", "Falha ao ler o sensor DHT!");
      return;
    } else {
      float hic = dht.computeHeatIndex(t, h, false);

      String message = "Umidade: " + String(h) + String('%');
      message += " Temperatura: " + String(t) + " *C";
      message += " Indice de calor: " + String(hic) + " *C";

      server.send(200, "text/plain", message);
    }
  } else {
    server.send(200, "text/plain", "Atualize mais uma vez!");
    return;
  }
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(security.getSsid(), security.getPwd());

  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(security.getSsid());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handle);
  server.onNotFound(handle);

  server.begin();
  Serial.println("HTTP server started");
  dht.begin();
  Serial.println("DHT22 sensor started");
  waiting();
}

void loop() {
  server.handleClient();
}
