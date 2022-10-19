# Resumen

En esta sección del proyecto **Habeetat** se construye el módulo encargado de medir la temperatura, humedad y concentración de CO2 dentro de la colmena. Se usa un microcontrolador ESP32-WROOM, un sensor de temperatura-Humedad DHT11 y un sensor de gases MQ135. El microcontrolador se programa para que mida las 3 variables y publique mediante el protocolo MQTT en un broker local, al mismo tiempo, se crea una base de datos con MySQL donde se guardan las lecturas de los sensores usando un flow creado en NodeRed; este flow nos ayuda a guardar las lecturas de los sensores en la base de datos y enviar notificaciones a un chat de Telegram usando un bot, el bot se programa para que reciba instrucciones y regrese consultas de la bases de datos, además de enviar notificaciones del estado de la colmena (alertas y datos) cada cierto periodo de tiempo. Los datos históricos y actuales recopilados son mostrados en gráficos en un dashboard de Grafana. 

# Material necesario
1. Computadora 
2. 1 microcontrolador ESP32-WROOM
2. 1 sensor DHT11
3. 1 sensor MQ135
4. 1 Protoboard 
5. Cables jumper MM
6. 1 resistencia de 10 kiloohms
7. 1 cable microusb a USB

# Software a utilizar

Para implementar la programación de microcontrolador se requiere la siguiente lista de software (todo el software es gratuito y con licencia de uso libre).

- [IDE de Arduino 1.8.20](https://www.arduino.cc/en/software)
- [NodeRed v3.0.2](https://nodered.org/)
- [Mosquitto 2.0.15](https://mosquitto.org/)
- [MySQL 8.0.30-0ubuntu0.22.04.1 (Ubuntu)](https://ubuntu.com/server/docs/databases-mysql)

Biblotecas de Arduino para programar el microontrolador y los sensores

- [Wifi](https://github.com/arduino-libraries/WiFi)
- [PubSubclient](https://github.com/knolleary/pubsubclient)
- [DHT11](https://github.com/adafruit/DHT-sensor-library)
- [Grafana v9.1.7](https://grafana.com/)
-  [Python 3.9](https://www.python.org/downloads/release/python-390/)
# Material de referencia


# Servicios

Se requiere la creación de un bot de Telegram, para usar tal servicio se requiere seguir los siguientes pasos

# Instrucciones para construir y programar el circuito de medición de temperatura, humedad y concentración de CO2

El circuito a crear es el siguiente
![mq135_DHT11_ESP32_bb](https://user-images.githubusercontent.com/72757419/196530284-8dddd8f8-5c5d-4881-b6c0-6d7075505e9f.png)

Deben tomarse en cuenta las siguientes consideraciones

Los pines del ESP32 se consideran así

![](../../../Fritzing/esp32-pinout-chip-ESP-WROOM-32.jpeg)

Los pines del sensor MQ135 son los siguientes

![MQ135-pinout](https://user-images.githubusercontent.com/72757419/196530385-ba1a9ea7-016d-4f87-aa35-57e096b4e68a.jpg)

Los pines del sensor DHT11 son los siguientes

![dht11](https://user-images.githubusercontent.com/72757419/196530433-02793838-1d82-4d0f-a192-28b7bf4f9647.png)

- El sensor MQ135 debe conectarse al microcontrolador a través de los siguientes pines
- 
|ESP32|MQ135|
|--|--|
| Vcc (5V)|Vcc|
|GND |GND|
|GPIO 34|A0|


- El sensor DHT11 debe conectarse al microcontrolador través de los siguientes pines

|ESP32|DHT11 |
|--|--|
| Vcc (5V)|Vcc  |
|GND |GND |
|GPIO 25 (14)|DATA (2)|

La tierra y la corriente se pueden conectar en paralelo para ser comunes. 


# Instrucciones de uso

# Resultados

# Evidencias

# Preguntas frecuentes

# Compatibilidad

# Bibliografía

# Créditos
