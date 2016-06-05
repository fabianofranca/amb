#include <Arduino.h>
#include <DHT.h>

struct DhtData {
	float temperatura;
	float humidity;
	float heatIndex;
};

class DhtClient {
private:
	bool _setuped;
	DHT _dht;
public:
	DhtClient(uint8_t pin, uint8_t type);
	void setup();
	DhtData getData();
};
