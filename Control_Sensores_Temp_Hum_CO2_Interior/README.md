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


Una vez conectado el ESP32 adquiriendo los datos de temperatura, humedad y CO2 creamos un flow en NodeRed ([Link del flow](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/tree/main/Control_Sensores_Temp_Hum_CO2_Interior/Flow_Nodered_monitoreo_interior_colmena)) que realiza las siguientes acciones:

  - Lectura y adquisición del archivo JSON con los datos desde el broker local hecho en MQTT para:
      1. Guardar los datos en una base de datos local hecha con MySQL ([Link detalles de la creación de base de datos](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/tree/main/Control_Sensores_Temp_Hum_CO2_Interior/Base_de_datos_My_SQL_interior_colmena))
      2. Generar reportes con el bot de telegram desde nodered  ([Link de los detalles para creación del bot de telegram con node red](https://flows.nodered.org/node/node-red-contrib-telegrambot))
        - El bot envía reportes programados o permite realizar consultas de los datos más recientes
      3. Envío de imágenes y vídeo con la esp32CAM y el bot de telegram desde nodered ([link del programa del esp32CAM](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/tree/main/Control_Camara_Video_Interior))
      4. El flow de node-red también tiene un panel donde podemos visualizar vídeo en tiempo real desde la colmena, está cámara se situa en el exterior de la colmena para vigilancia
      5. Envío de la predicción del peso de la colmena en los siguientes días ([Link del código de predicción](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/tree/main/Prediccion_Peso_Colmena))
      6. Cuando las condiciones de Temperatura, humedad o concentración de CO2 no son las favorables para la colmena también se envía un mensaje de alerta.

      

Notas del uso de los programas y del flow de node red:

- Colocar el SSID y el password de la red Wifi a la que se conectará el ESP32 WROOM al igual que la ESP32CAM
  - `const char* ssid = "NOMBRE DE LA RED";`
  - `const char* password = "Contrasena";`
- Definir los datos de la ip del broker local, deben tener el siguiente formato
   - `const char* mqtt_server = "192.168.xxx.xx";`
   - `IPAddress server(192,168,xxx,xx);`
- El json que envía los datos con los sensores al broker mqtt local tiene el siguiente formato
  - `String json = "{\"id\":\"MQ135_DHT11\",\"ValorAnalogico\":"+String(analogValue)+",\"VoltajeAnalogico\":"+String(analogVolts)+",\"Temperatura\":"+String(t)+",\"Humedad\":"+String(h)+"}";`
  es importante que sea en este formato porque posteriormente en el flow de NodeRed se leerá el jason
  - El tópico de MQTT donde se publican los datos es "Habeetat/sensores/dht11mqtt", en el programa de arduino corresponde a la instrucción
  - `client.publish("Habeetat/sensores/dht11mqtt", char_array);`

  Para leer los datos desde el broker en Nodered y guardarlos en la base de datos local se configura un nodo MQTT que se suscriba al tópico `Habeetat/sensores/dht11mqtt` y se programa la función que nos permita guardar en la base de datos local (el nombre de la base es __sensor_MQ_DHT__, la tabla donde se insertan los datos es __Datos_Sensores___), el código para la función *conexión mysql* es

  `msg.topic = "INSERT INTO Datos_Sensores (id_sensor, ValorAnalogico, VoltajeAnalogico, Temperatura, Humedad) VALUES ('" + msg.payload.id + "'," + msg.payload.ValorAnalogico + "," + msg.payload.VoltajeAnalogico + "," + msg.payload.Temperatura + "," + msg.payload.Humedad +");return msg;`

<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_nodo_mqtt_01.jpg" width="1000" height="200" />

Los datos son guardados en la base de datos que posteriormente será la fuente de datos para el panel de grafana.

<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_grafana_panel_03.jpg" width="1000" height="500" />

El flow de Nodered se diseña para adquirir vídeo en tiempo real y al mismo tiempo tomar una imagen que se almacena de forma local y que posteriormente se puede enviar a través del chat de telegram haciendo la petición enviando la palabra **imagen**. El flow contiene un dashboard donde se ve el vídeo en tiempo real desde el ESP32CAM y la imagen capturada.

<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_imagen_06.jpg" width="1000" height="600" />

<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_node_red_dashboard_08.jpg" width="1000" height="600" />

El paquete de Nodered que nos permite enviar y recibir con un bot de telegram es [node-red-contrib-telegrambot](https://flows.nodered.org/node/node-red-contrib-telegrambot), para poder ser usado debe crearse un bot desde la aplicación de Telegram, usar la API key, conseguir el ID del chat donde se publicara, configurar los nodos __receiver__ con ayuda de un nodo __funcion__ para que acepten una palabra clave y despues el nodo __sender__ envíe la información solicitada.

<p align="center">
<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_chat_sender_telegram_02.jpg" width="1000" height="300" />
</p>

En este proyecto se puede hacer consulta usando las siguientes opciones

|Palabra a través del chat |Acción del bot|
|--|--|
| consulta| Envía los datos más recientes de los sensores |
| imagen | Envía una imagen reciente de la cámara en la colmena |
|prediccion | Envía 3 imágenes con resultados de la predicción del peso de la colmena en los siguientes días|

Ejemplo de la función para enviar datos de los sensores a través del __sender__

`if (msg.payload.content == "consulta" || msg.payload.content == "Consulta")
{
    msg.payload = {};
    msg.payload.chatId = -XXXXXXXXX;  // Aquí se coloca el ID del chat a usar para enviar mensajes
    msg.payload.type = 'message';
    var espacio = " \n";
    msg.payload.content ="\u{1F41D}" + " Datos de la colmena " + "\u{1F41D}" + espacio + "Nombre del sensor: " + global.get('id') + espacio + "\u{1F321}" + "Temperatura: " + global.get("Temperatura") + " °C" + espacio + "\u{2614}" + "Humedad: " + global.get("Humedad") + " %" + espacio +"\u{1F32B}" + "Concentración de CO2: " + espacio + global.get("VoltajeAnalogico") + " PPM"+
    espacio + "Envia <consulta> para acceder a los datos más actuales de la colmena, envía <prediccion> para el pronostico del peso de la colmena, envía <imagen> para recibir una fotografía actual de la colmena";
    return msg;
}`









## Resultados
Captura de pantalla del monitor serial del IDE de arduino con los datos de salida de las lecturas de los sensores y el archivo json que se publica en el broker local
![imagen](https://user-images.githubusercontent.com/72757419/200640844-e3ce6719-60ad-45df-b4fe-98c2a3800893.png)

## Evidencias

## Preguntas frecuentes

## Compatibilidad

## Bibliografía

## Créditos
