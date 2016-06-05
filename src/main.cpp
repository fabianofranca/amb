#include <ESP8266WiFi.h>
#include <Security.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DhtClient.h>

#define DHTPIN 5
#define DHTTYPE DHT22

#define ORG "v0u23l"
#define DEVICE_TYPE "ESP8266"
#define DEVICE_ID "Prototipo"
#define TOKEN "K1YVb3Nm63Pw9P469D39qvfw4c49nD37"

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

//iot-2/evt/<event-id>/fmt/<format>
const char publishTopic[] = "iot-2/evt/status/fmt/json";

Security security;
DhtClient dhtClient(DHTPIN, DHTTYPE);
WiFiClient wifiClient;

void callback(char* topic, byte* payload, unsigned int payloadLength) {
	Serial.print("callback invoked for topic: ");
	Serial.println(topic);
}

PubSubClient mqttClient(server, 1883, callback, wifiClient);

int publishInterval = 30000;

void wifiConnect() {
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
}

void mqttConnect() {
	if (!mqttClient.connected()) {
		Serial.print("Reconnecting MQTT client to ");
		Serial.println(server);

		while (!mqttClient.connect(clientId, authMethod, token)) {
			Serial.print(".");
			delay(500);
		}

		Serial.println();
	}
}

void setup() {
	Serial.begin(9600);
	wifiConnect();
	dhtClient.setup();
	mqttConnect();
}

void publishData() {
	float t = dhtClient.getData().temperatura;
	float h = dhtClient.getData().humidity;
	float hic = dhtClient.getData().heatIndex;

	String payload = "{\"d\":{\"temperature\":";
	payload += String(t) + ", ";
	payload += "\"humidity\":";
	payload += String(h) + ", ";
	payload += "\"heatIndex\":";
	payload += String(hic);
	payload += "}}";

	Serial.print("Sending payload: ");
	Serial.println(payload);

	if (mqttClient.publish(publishTopic, (char*)payload.c_str())) {
		Serial.println("Publish OK");
	}
	else {
		Serial.println("Publish FAILED");
	}
}

void loop() {
	if (!mqttClient.loop()) {
		mqttConnect();
	}

	publishData();

	delay(publishInterval);
}