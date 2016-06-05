#include "WifiHelper.h"

WifiHelper::WifiHelper(const char* ssid, const char* password) :
	_ssid(ssid), _password(password)
{
}

void WifiHelper::connect() {
	WiFi.begin(_ssid, _password);

	Serial.println("");

	// Wait for connection
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(_ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
}