#include <Arduino.h>

class Config {
  public:
    Config();
    const char* getSsid();
    const char* getPwd();
	String getOrg();
	String getDeviceType();
	String getDeviceID();
	String getToken();
};