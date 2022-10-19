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

- Sistema operativo Ubuntu 22.02 corriendo en la computadora
- IDE de Arduino 1.8.20
- NodeRed v3.0.2
- Mosquitto 2.0.15
- MySQL 8.0.30-0ubuntu0.22.04.1 (Ubuntu)
- Biblotecas de Arduino para programar el microontrolador y los sensores
	+ Wifi
	+ PubSubclient
	+ DHT11
- Grafana v9.1.7
- Python 3.9

# Material de referencia

# Servicios

Se requiere la creación de un bot de Telegram, para usar tal servicio se requiere seguir los siguientes pasos

# Instrucciones para construir y programar el circuito de medición de temperatura, humedad y concentración de CO2

El circuito a crear es el siguiente
![mq135_DHT11_ESP32_bb](https://user-images.githubusercontent.com/72757419/196530284-8dddd8f8-5c5d-4881-b6c0-6d7075505e9f.png)

Deben tomarse en cuenta las siguientes consideraciones

Los pines del sensor MQ135 son los siguientes

![MQ135-pinout](https://user-images.githubusercontent.com/72757419/196530385-ba1a9ea7-016d-4f87-aa35-57e096b4e68a.jpg)

Los pines del sensor DHT11 son los siguientes

![dht11](https://user-images.githubusercontent.com/72757419/196530433-02793838-1d82-4d0f-a192-28b7bf4f9647.png)

- El sensor MQ135 debe conectarse al microcontrolador de la siguiente forma
- Los pines 


- El sensor DHT11 debe conectarse al microcontrolador de la siguiente forma



# Instrucciones de uso

# Resultados

# Evidencias

# Preguntas frecuentes

# Compatibilidad

# Bibliografía

# Créditos
