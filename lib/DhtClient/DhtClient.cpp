#include "DhtClient.h"

DhtClient::DhtClient(uint8_t pin, uint8_t type) :
	_dht(pin, type)
{
}

void DhtClient::setup() {
	_dht.begin();

	Serial.println("DHT22 sensor starting");

	int loading = 0;

	while (loading < 2000) {
		Serial.print(".");
		delay(500);
		loading += 500;
	}

	Serial.println();
	Serial.println("DHT22 sensor started");

	_setuped = true;
}

DhtData DhtClient::getData() {
	DhtData data;

	if (_setuped) {
		data.temperatura = _dht.readTemperature();
		data.humidity = _dht.readHumidity();
		data.heatIndex = _dht.computeHeatIndex(data.temperatura, data.humidity, false);
	}
	else {
		Serial.println("Invoke DhtCliente.setup()");

		data.temperatura = 0;
		data.humidity = 0;
		data.temperatura = 0;
	}

	return data;
}