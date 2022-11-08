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

## Software a utilizar

Para implementar la programación de microcontrolador se requiere la siguiente lista de software (todo el software es gratuito y con licencia de uso libre).

- [IDE de Arduino 1.8.20](https://www.arduino.cc/en/software)
- [NodeRed v3.0.2](https://nodered.org/)
- [Mosquitto 2.0.15](https://mosquitto.org/)
- [MySQL 8.0.30-0ubuntu0.22.04.1 (Ubuntu)](https://ubuntu.com/server/docs/databases-mysql)
- [Grafana v9.1.7](https://grafana.com/)
- [Python 3.9](https://www.python.org/downloads/release/python-390/)

Biblotecas de Arduino para programar el microontrolador y los sensores

- [Wifi](https://github.com/arduino-libraries/WiFi)
- [PubSubclient](https://github.com/knolleary/pubsubclient)
- [DHT11](https://github.com/adafruit/DHT-sensor-library)

## Material de referencia


## Servicios

Se requiere la creación de un bot de Telegram, para usar tal servicio se requiere seguir los siguientes pasos

## Instrucciones para construir y programar el circuito de medición de temperatura, humedad y concentración de CO2

El circuito a crear es el siguiente
![mq135_DHT11_ESP32_bb](https://user-images.githubusercontent.com/72757419/196530284-8dddd8f8-5c5d-4881-b6c0-6d7075505e9f.png)

Deben tomarse en cuenta las siguientes consideraciones para el armado del circuito

Los pines del ESP32 se consideran así de acuerdo a la siguiente nomenclatura

![imagen](https://user-images.githubusercontent.com/72757419/200460988-6ad9b2ea-0108-404c-bbcd-777da94db86a.png)

Los pines del sensor MQ135 son los siguientes

![MQ135-pinout](https://user-images.githubusercontent.com/72757419/196530385-ba1a9ea7-016d-4f87-aa35-57e096b4e68a.jpg)

Los pines del sensor DHT11 son los siguientes

![dht11](https://user-images.githubusercontent.com/72757419/196530433-02793838-1d82-4d0f-a192-28b7bf4f9647.png)

- El sensor MQ135 debe conectarse al microcontrolador a través de los siguientes pines

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

La siguiente imagen muestra el circuito del MQ135 y el DHT11 conectados al ESP32 WROOM

Vista frontal
![imagen](https://user-images.githubusercontent.com/72757419/200628857-9bebe0c3-615e-44cf-809f-d3c2b28c7766.png)

Vista Trasera
![imagen](https://user-images.githubusercontent.com/72757419/200629030-be07c08a-5266-4a00-9715-e6927325ad53.png)


## Instrucciones para la programación del ESP32 WROOM

El programa para leer los sensores se encuentra en la carpeta [Carpeta]. Este programama hace uso de las bibliotecas  WiFI, PubSubClient y DHT11 por lo que es necesario instalarlas en el IDE de Arduino antes de subir el programa al ESP32, así como de preparar todo el entorno en sistema operativo (Ubuntu) para que se conecte el ESP32 WROOM a la computadora (ver material de referencias de configuración del IDE de Arduino y ESP32). Una vez que se realizan las lecturas del sensor estás son publicadas en un broker local mediante el protocolo MQTT usando mosquitto por lo que hay que configurarlo también en la computadora (ver material de referencia de configuración). 

El programa del ESP32 WROOM permite las siguiente acciones:

- Conexión del microcontrolador a Wifi
- Lectura del Voltaje analógico del sensor MQ-135 (concentración de CO2)
- Lectura de Temperatura y Humedad con el sensor DHT11
- Publicación y suscripción a tópicos en el broker local usando MQTT

Notas del uso del programa:

- Colocar el SSID y el password de la red Wifi a la que se conectará el ESP32 WROOM
    `const char* ssid = "NOMBRE DE LA RED";`
    `const char* password = "Contrasena";`





## Resultados


## Evidencias

## Preguntas frecuentes

## Compatibilidad

## Bibliografía

## Créditos
