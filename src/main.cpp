#include <Arduino.h>
#include <Config.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DhtClient.h>
#include <WiFiHelper.h>

#define DHTPIN 5
#define DHTTYPE DHT22

Config config;

String server = config.getOrg() + ".messaging.internetofthings.ibmcloud.com";
const char* authMethod = "use-token-auth";
String clientId = "d:" + config.getOrg() + ":" + config.getDeviceType() + ":" + config.getDeviceID();

//iot-2/evt/<event-id>/fmt/<format>
const char publishTopic[] = "iot-2/evt/status/fmt/json";

WifiHelper wifiHelper(config.getSsid(), config.getPwd());
DhtClient dhtClient(DHTPIN, DHTTYPE);
WiFiClient wifiClient;

void callback(char* topic, byte* payload, unsigned int payloadLength) {
	Serial.print("callback invoked for topic: ");
	Serial.println(topic);
}

PubSubClient mqttClient(server.c_str(), 1883, callback, wifiClient);

int publishInterval = 30000;

void mqttConnect() {
	if (!mqttClient.connected()) {
		Serial.print("Reconnecting MQTT client to ");
		Serial.println();
		Serial.println(server.c_str());

		while (!mqttClient.connect(clientId.c_str(), authMethod, config.getToken().c_str())) {
			Serial.print(".");
			delay(500);
		}

		Serial.println();
	}
}

void setup() {
	Serial.begin(9600);
	Serial.println(config.getOrg());
	wifiHelper.connect();
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