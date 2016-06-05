#include <Arduino.h>
#include <ESP8266WiFi.h>

class WifiHelper {
private:
	const char* _ssid;
	const char* _password;
public:
	WifiHelper(const char* ssid, const char* password);
	void connect();
};
