# amb

## v0.0.1

Prototipo  simples composto por um ESP8266(NodeMCU) mais um sensor de temperatura e umidade DHT22. Exibe a temperatura e acessando por IP.

Utilizei a plataforma de desenvolvimento [PlatformIO](http://platformio.org/)

## v0.0.2

Enfrentei problemas utilizando o PlatformIO + Atom, decidi converter o projeto para PlatformIO + Visual Studio. Aparentemente as coisas melhoraram.

### Conectando ao Wifi

Para fazer o ESP8266 se conectar a uma rede WiFi é necessário criar o arquivo abaixo:

*amb/lib/Security/src/Security.cpp*

```
#include "Security.h"

Security::Security() {
}

const char* Security::getSsid() {
  return "SSID da sua rede";
}

const char* Security::getPwd() {
  return "Senha da sua rede";
}
```
