# amb

## v0.0.1

Prototipo  simples composto por um ESP8266(NodeMCU) mais um sensor de temperatura e umidade DHT22. Exibe a temperatura e acessando por IP.

Utilizei a plataforma de desenvolvimento [PlatformIO](http://platformio.org/)

## v0.0.2

Enfrentei problemas utilizando o PlatformIO + Atom, decidi converter o projeto para PlatformIO + Visual Studio. Aparentemente as coisas melhoraram.

## v0.0.3

Atualização de documentação.

## v0.1.0

O webserver foi removido. Foi adicionado suporte ao MQTT usando o plano gratuito do Bluemix.
Refatoração parcial do código. Foram criadas algumas "libs" para melhor organização do código.

### Instalando Libraries

```
platformio lib install 19 // Adafruit-DHT
platformio lib install 64 // Json
platformio lib install 89 // PubSubClient - MQTT
```

### Conectando ao Wifi

Para fazer o ESP8266 se conectar a uma rede WiFi é necessário criar o arquivo abaixo:

*amb/lib/Config/src/Config.cpp*

```
#include "Config.h"

Config::Config() {
}

const char* Config::getSsid() {
  return "SSID da sua rede";
}

const char* Config::getPwd() {
  return "Senha da sua rede";
}

String Config::getOrg() {
	return "ID da organização";
}

String Config::getDeviceType() {
	return "Tipo de dispositivo";
}

String Config::getDeviceID() {
	return "ID do dispositivo";
}

String Config::getToken() {
	return "Token de autenticação";
}
```

### [Protótipo V1](http://fritzing.org/projects/amb-prototype-1)

<img src="http://fritzing.org/media/fritzing-repo/projects/a/amb-prototype-1/images/amb.png" width="350">
