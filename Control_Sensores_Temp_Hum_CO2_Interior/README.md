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

[Telegram bot API](https://core.telegram.org/bots/api)

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

      

## Notas del uso de los programas y del flow de node red:

- Colocar el SSID y el password de la red Wifi a la que se conectará el ESP32 WROOM al igual que la ESP32CAM
  - `const char* ssid = "NOMBRE DE LA RED";`
  - `const char* password = "Contrasena";`
- Definir los datos de la ip del broker local, deben tener el siguiente formato
   - `const char* mqtt_server = "192.168.xxx.xx";`
   - `IPAddress server(192,168,xxx,xx);`
- El json que envía los datos con los sensores al broker mqtt local tiene el siguiente formato
  - `String json = "{\"id\":\"MQ135_DHT11\",\"ValorAnalogico\":"+String(analogValue)+",\"VoltajeAnalogico\":"+String(analogVolts)+",\"Temperatura\":"+String(t)+",\"Humedad\":"+String(h)+"}";`
  es importante que sea en este formato porque posteriormente en el flow de NodeRed se leerá el json
  - El tópico de MQTT donde se publican los datos es "Habeetat/sensores/dht11mqtt", en el programa de arduino corresponde a la instrucción
  - `client.publish("Habeetat/sensores/dht11mqtt", char_array);`

  Para leer los datos desde el broker en Nodered y guardarlos en la base de datos local se configura un nodo MQTT que se suscriba al tópico `Habeetat/sensores/dht11mqtt` y se programa la función que nos permita guardar en la base de datos local (el nombre de la base es __sensor_MQ_DHT__, la tabla donde se insertan los datos es __Datos_Sensores___), el código para la función *conexión mysql* es

  `msg.topic = "INSERT INTO Datos_Sensores (id_sensor, ValorAnalogico, VoltajeAnalogico, Temperatura, Humedad) VALUES ('" + msg.payload.id + "'," + msg.payload.ValorAnalogico + "," + msg.payload.VoltajeAnalogico + "," + msg.payload.Temperatura + "," + msg.payload.Humedad +");return msg;`

<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_nodo_mqtt_01.jpg" width="1000" height="200" />

Los datos son guardados en la base de datos que posteriormente será la fuente de datos para el panel de grafana.

<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_grafana_panel_03.jpg" width="1000" height="500" />

El paquete de Nodered que nos permite enviar y recibir con un bot de telegram es [node-red-contrib-telegrambot](https://flows.nodered.org/node/node-red-contrib-telegrambot), para poder ser usado debe crearse un bot desde la aplicación de Telegram, usar la API key, conseguir el ID del chat donde se publicara, configurar los nodos __receiver__ con ayuda de un nodo __funcion__ para que acepten una palabra clave y despues el nodo __sender__ envíe la información solicitada.

En este proyecto se puede hacer consulta usando las siguientes opciones:

|Palabra a través del chat |Acción del bot|
|--|--|
| consulta| Envía los datos más recientes de los sensores |
| imagen | Envía una imagen reciente de la cámara en la colmena |
|prediccion | Envía 3 imágenes con resultados de la predicción del peso de la colmena en los siguientes días|

Ejemplo de la función para enviar datos de los sensores a través del __sender__
~~~
if (msg.payload.content == "consulta" || msg.payload.content == "Consulta")
{
    msg.payload = {};
    msg.payload.chatId = -XXXXXXXXX;  // Aquí se coloca el ID del chat a usar para enviar mensajes
    msg.payload.type = 'message';
    var espacio = " \n";
    msg.payload.content ="\u{1F41D}" + " Datos de la colmena " + "\u{1F41D}" + espacio + "Nombre del sensor: " + global.get('id') + espacio + "\u{1F321}" + "Temperatura: " + global.get("Temperatura") + " °C" + espacio + "\u{2614}" + "Humedad: " + global.get("Humedad") + " %" + espacio +"\u{1F32B}" + "Concentración de CO2: " + espacio + global.get("VoltajeAnalogico") + " PPM"+
    espacio + "Envia <consulta> para acceder a los datos más actuales de la colmena, envía <prediccion> para el pronostico del peso de la colmena, envía <imagen> para recibir una fotografía actual de la colmena";
    return msg;
}
~~~

<p align="center">
<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_chat_sender_telegram_02.jpg" width="1000" height="300" />
</p>



El flow de Nodered se diseña para adquirir vídeo en tiempo real y al mismo tiempo tomar una imagen que se almacena de forma local y que posteriormente se puede enviar a través del chat de telegram haciendo la petición enviando la palabra **imagen**. El flow contiene un dashboard donde se ve el vídeo en tiempo real desde el ESP32CAM y la imagen capturada.

Nodos que envía la imagen con el bot de telegram

![imagen](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_env%C3%ADo_imagen_05.jpg)


Se guarda la imagen cada minuto para su envío cuando se consulta por telegram, los nodos encargados de la captura, guardado de la imagen y publicación del vídeo en el dashboard de node red son los siguientes:

![imagen](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_env%C3%ADo_imagenes_04.jpg)


Se configuran dos nodos __template__ de node red para poder ver el vídeo y la fotografía en el dashboard, el código de los nodos es el siguiente:

Nodo _tomar fotografía_

~~~
<div style="margin-bottom: 10px;">
    <img src="http://192.168.100.xxx:81/capture" width="1500px" height="750px">
</div>
~~~

La línea `http://192.168.100.xxx:81/capture` debe incluir la ip completa que nos envía el monitor serial de arduino cuando programamos el ESP32 CAM.

Nodo _imagen de la cámara_

~~~
<div style="margin-bottom: 10px;">
    <img src="http://192.168.100.xxx" width="1500px" height="750px">
</div>
~~~

La línea `http://192.168.100.xxx` debe incluir la ip completa que nos envía el monitor serial de arduino cuando programamos el ESP32 CAM.

El dashboard con el vídeo y la fotografía se muestran a continuación

<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_node_red_dashboard_08.jpg" width="1000" height="600" />

Cuando se envía _imagen_ al chat de telegram La imagen se recibe en el chat de elegido

<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_imagen_06.jpg" width="1000" height="600" />


La predicción del comportamiento del peso de la colmena se realiza usando una biblioteca llamada _Prophet_ desarrollada por el equipo de Facebook y de acuerdo a la [página oficial de Prophet ](https://facebook.github.io/prophet/), _Prophet es un procedimiento para pronosticar datos de series temporales basado en un modelo aditivo en el que las tendencias no lineales se ajustan a la estacionalidad anual, semanal y diaria, además de los efectos de los datos faltantes. Funciona mejor con series temporales que tienen fuertes efectos estacionales y varias temporadas de datos históricos. Prophet es resistente a los datos faltantes y los cambios en la tendencia, y por lo general maneja bien los valores atípicos._ Esto tipo de comportamientos son comunes en sistemas donde se miden variables climáticas, además es relativamente fácil de implementar en Python. Dado que no se cuenta todavía con datos reales para hacer la implementación de la predicción, se toma un conjunto de datos reales que han sido medidos _in situ_ en colmenas ([dataset usado para la predicción](https://www.kaggle.com/datasets/se18m502/bee-hive-metrics)), de tal forma que los datos esperados en nuestras mediciones tengan características similares a este data set. 

Para hacer la petición de la predicción de los datos de peso de la colmena se envía la palabra _prediccion_ en el chat de telegram, esto retornará 3 gráficas que mostrarán los datos históricos del peso de la colmena (se define en el programa el tiempo de predicción), junto con la línea de tendencia y la predicción del peso en los siguientes días. De forma adicional hay 2 gráficas que nos muestran las variaciones estadísticas por hora del peso a lo largo día y los puntos (días) donde existe una variación signfificativa del peso. Estas gráficas juntos con los datos recopilados tienen el objetivo de ser el soporte de la toma de decisiones con el fin de mantener la salud de la colmena. 

Se muestra a continuación un ejemplo de la petición

<p align="center">
<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_prediccion_07.jpg" width="800" height="700" />
</p>

El programa de la predición se realizó en Python y se ejecuta autamáticamente usando un administrador de procesos en segundo plano para Linux llamado **Cron** que ejecuta procesos, programas o scripts a intervalos regulares de tiempo, es decir, con crontab podemos elegir en qué momento ejecutar algo. Las tareas de Cron se registran y administran en un archivo especial llamado **_crontab_**. Cada perfil de usuario del sistema LInux puede tener su propio crontab para programar tareas, que se almacenan en __/var/spool/cron/crontabs__. En este proyecto se programaron las tareas para que se ejecute la predicción de forma automatica cada 8 días los lunes a las 00:00 horas y que los datos estén disponibles para toda la semana en el momento que el usuario invoque la predicción. Una vez editado el archivo crontab se guarda, se cierra y estará trabajando en segundo plano hasta que se desactive.

El archivo crontab editado para este proyecto se ve así

<p align="center">
<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_cron_archivo_11.jpg" width="1000" height="400" />
</p>

La última línea es la que específica la hora y día en que se ejecutará el comando que invoca el script de python para la predicción.  En nuestrop caso, la última línea indica que se active un ambiente virtual llamado _profeta_ y ajecute el archivo .py con el programa para la predicción.

## Resultados
A continuación se muestran un informe gráfico de los resultados de todo el proceso de creación de los sensores internos de la colmena inteligente:

### Resultado programación de los sensores en Arduino

 En esta imagen se muestra los valores obtenidos por los sensores DHT11 y MQ135, se observan los valores de temperatura, humedad obtenidos con el DHT11 y el valor de voltaje analógico obtenido con el sensor MQ135. Eso valores se formatean para crear un json y publicarlos en el broker local y posteriormente leerlos en node-red para publicarlos en la base de datos local. El json creado tiene los siguientes datos:
~~~
{"id":"MQ135_DHT11","ValorAnalogico":1017,"VoltajeAnalogico":960,"Temperatura":18.80,"Humedad":54.00}
~~~
- id del sensor (MQ135_DHT11)
- Valor analógico
- Valor digital (está es una medida directa del valor de concentración de CO2 en PPM)
- Temperatura (ºC)
- Humedad (%)

<p align="center">
<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_salida_monitor_serial_arduino-dht11mq135.jpg"  />
</p>

### Resultados del flow de nodered

Los datos del sensor son enviados al broker mosquitto al tópico _Habeetat/sensores/dht11mqtt__ donde un nodo mqtt lee los datos y los publica en la base de datos __Sensor_MQ_DHT__ en la tabla _Datos_sensores_, a continuación se muestra la sección del flow que realiza la acción de publicar en la base de datos y la lectura 


En esta imagen se puede observar el tópico en donde el flow lee en el tópico de mosquitto, descargar el json y publica los datos en la base de datos con ayuda de una función programada en javascript
<p align="center">
<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_node_red_base_de_datos_15.jpg" width="1000" />
</p>

Los datos guardados en la base de datos local se pueden leer usando la terminal de linux 

<p align="center">
<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_base_de_datos_sensores_16.jpg" width="1000" />
</p>

### Resualtados de la medición en panel de Grafana

Los datos históricos guardados en la base de datos se pueden revisar en el panel de Grafana creado para este propósito, además, se pueden visualizar los datos actuales obtenidos por los sensores.

<p align="center">
<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_panel_grafana_resultados_18.jpg" width="1000" />
</p>

### Resultados de la predicción del peso de la colmena

En este trabajo se predice el peso de la colmena dado que es un factor que indica directamente cuál es el estado de salud de la colmena, para esto usamos el modelo matematico **Prophet** propuesto en el [artículo de Taylor, S. J., & Letham](https://peerj.com/preprints/3190.pdf), investigadores de equipo de ciencia de datos de Facebook. 

El modelo es útil para nuestros datos ya que son datos que muestran comportamientos no lineales, además de que tienen ciertos componentes periódicos y además puede darse el caso de que haya datos faltantes o valores atípicos. El modelo toma en cuenta todo lo anterior para generar una línea de tendencia y predecir los valores en periodos de tiempo que nosotros decidamos. De acuerdo a la página oficial del proyecto **Prophet** el modelo es rápido y preciso, completamente automáticos y los pronósticos son ajustables, es decir, hay parámetros que podemos ajustar para predecir con mayor precisión.   Este modelo se ha usado para predecir precio de acciones, demanda de servicios, etc. Incluso Amazon Web Services lo tiene dentro de su documentación como un algoritmo de predicción [link a AWS](https://docs.aws.amazon.com/es_es/forecast/latest/dg/aws-forecast-recipe-prophet.html).

Esta predicción se realiza cada 8 días de forma automática en segundo plano usando _Cron_ como se describió anteriormente.

La implementación del modelo para nuestro conjunto de datos nos permite obtener tres gráficas:

- Gráfica 1 (Figure 1). Muestra los datos del peso de la colmena de 1 mes anterior y la predicción de 2 días adelante. En esta gráfica se muestran los datos obtenidos con los sensores (puntos negros), la línea de tendencia (línea azul) y el intervalo de incertidumbre de la prediccción (franja azul).

- Gráfica 2 (Figure 2). En el gráfico superior se muestra la línea de tendencia del modelo y la prediccción, el el gráfico inferior un análisis estadístico de la variación del peso de acuerdo a la hora del día en todo el intervalo de tiempo de los datos considerados para el análisis.

- Gráfica 3 (Figure 3). Muestra los días en el que se observa una mayor variación del peso, esto es útil porque muestra los días donde hay un cambio en las tendencias de los datos.

A partir de estas gráficas se pueden tomar decisiones sobre la salud de la colmena. 

<p align="center">
<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_prediccion_profeta_17.jpg" width="1000" />
</p>

## Evidencias

Videos de youtube

1. Funcionamiento de los sensores con MQTT, NodeRed y la base de datos MySQL.

https://www.youtube.com/watch?v=seBQrWVgVqA



2. Funcionamiento del chat de Telegram

## Preguntas frecuentes

## Compatibilidad

## Bibliografía

1. Taylor, S. J., & Letham, B. (2018). Forecasting at scale. The American Statistician, 72(1), 37-45.

## Créditos
