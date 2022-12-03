## Introducción

En este apartado sobre el desarrollo del proyecto Capstone, Habeetat Colmena saludable, se describe cómo se implementaron los siguientes puntos:

1. La adquisición de la temperatura, humedad y peso; circundantes a la colmena.
2. Activación de un actuador que funcione con 127Vca y hasta 1500W de potencia.
3. Implementación de una base de datos en MySQL para llevar un registro de las variables detectadas.
4. Interfaz gráfica y de control en NodeRed.
5. Graficado de variables registradas en Grafana.
6. Envío de mensaje de alerta por el servicio de mensajería Telegram.
7. Solicitud de estado de las condiciones de las variables en tiempo real por mensaje de un Bot en Telegram.

## Material necesario

- 1 [ESP32CAM](https://docs.ai-thinker.com/en/esp32-cam). Tarjeta de desarrollo
- 1 [FTDI](https://ftdichip.com/wp-content/uploads/2020/08/DS_FT232R.pdf). Tarjeta controladora USB
- 1 [DHT11](https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf). Sensor de temperatura y humedad
- 1 [HX711](https://cdn.sparkfun.com/datasheets/Sensors/ForceFlex/hx711_english.pdf). ADC-24 bits para escalas de peso.
- 1 [Celda de carga para 20Kg.](https://naylampmechatronics.com/sensores/157-celda-de-carga-20kg.html). También conocida como galga extensiométrica.
- 1 Resistor de 100ohms. (Café,Negro,Café,Dorado)
- 1 Resistor de 220ohms. (Rojo,Rojo,Café,Dorado)
- 1 Resistor de 330ohms. (Naranja,Naranja,Café,Dorado)
- 1 Resistor de 360ohms. (Naranja,Azul,Café,Dorado)
- 1 Resistor de 10Kohms. (Café,Negro,Naranja,Dorado)
- 1 BT137 (TRIAC)
- 1 [MOC3043, optoacoplador](https://www.datasheetq.com/MOC3043-doc-Motorola)
- 1 Capacitor de 10nF (103)
- 1 cable USB a USB mini.
- Jumpers MM.

## Software necesario

En la experimentación de está práctica se debe de contar con el siguiente software libre:

- Ubuntu 20.04
- Arduino IDE
- Mosquitto MQTT Broker, Listener en puerto 1883 para 0.0.0.0 y conexiones autentificadas activadas.
- NodeJS. NPM, NodeRed y Node Dashboard.
- MySQL
- Grafana

## Material de referencia

Previamente a la realización de está práctica, ha sido necesario el estudio de distitos temas, que se encuentran en la plataforma [edu.codigoiot.com](https://www.codigoiot.com/), en donde se explican conceptos y configuraciones necesarias, tales como:

- Instalación de virtual Box y Ubuntu 20.04
- Configuración de Arduino IDE para ESP32CAM
- Instalación de NodeRed
- Introducción a NodeRed
- Instalación de Mosquitto MQTT

En los siguientes enlaces se decriben de manera partícular los trabajos que dan soporte a está etapa del proyecto.

- [Sensado de temperatura y humedad con DHT11](https://github.com/OmarAbundis/Sensado-de-temperatura-y-humedad-con-el-DHT11)
- [Sensado de peso con el HX711](https://github.com/OmarAbundis/Sensado-de-peso-con-el-HX711-y-el-ESP32CAM)
- [Etapa de desacoplado](https://github.com/OmarAbundis/Etapa-de-desacoplado-con-MOC-y-TRIAC-para-activacion-de-carga-a-127Vca)

También se recomienda el estudio de las siguientes páginas, donde se explican algunas implementaciones de una báscula electrónica usando la tarjeta de desarrollo Arduino UNO.

- [bogde/HX711](https://github.com/bogde/HX711)
- [Tutorial trasmisor de celda de carga HX711, Balanza Digital](https://naylampmechatronics.com/blog/25_tutorial-trasmisor-de-celda-de-carga-hx711-balanza-digital.html)
- [Balanza Electronica con HX711 y Arduino](https://controlautomaticoeducacion.com/arduino/balanza-electronica-hx711-arduino/)
- [Balanza WIFI con ESP32](https://www.prometec.net/balanza-wifi-esp32/)
- [Celda de carga 50 kg arduino programacion](https://arduinoque.com/arduino/celda-de-carga-50-kg-arduino-programacion/)
- [ESP32 Troubleshooting Guide](https://randomnerdtutorials.com/esp32-troubleshooting-guide/)

## Servicios

Adicional a lo ya indicado en líneas superiores, también es necesario contar con los siguientes servicios:

[HiveMQ](https://www.hivemq.com/public-mqtt-broker/). Es un broker público y que no demanda de contar con una cuenta.

[Telegram Messenger](https://telegram.org/?setln=es). Servicio de mensajería.

### 1. La adquisición de la temperatura, humedad y peso

**Nota:** Se recomienda revisar la información previamente citada, antes de comenzar con el armado del circuito electrónico, para reducir la probabilidad de realizar malas conexiones entre los dispositivos, fallas en la polarización y en consecuencia el daño permanente de los dispositivos o daño parcial o total de su equipo de cómputo.

1.  Se debe de armar el circuito electrónico mostrado en la figura teniendo cuidado de conectar a las terminales indicadas del ESP32-CAM, y cuidar la polaridad de los dispositivos.

![A027](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A027.gif)

***Circuito Electrónico de Control y Adquisición de Peso, Temperatura y Humedad, y Control de Carga***.

En las siguientes tablas, se puede observar la correspondencia de las terminales que se deben de conectar entre el ESP32-CAM y los distintos sensores y el actuador.

***Terminales de Conexión de ESP32-CAM a DHT11***.
| ESP32-CAM | DTH11|
| ----------|------|
| GPIO 2    | DATA |
| 5V        | Vcc  |
| GND       | GND  |


***Terminales de Conexión de ESP32-CAM a HX711***.
| ESP32-CAM | HX711 |
|-----------|-------|
| Vcc = 5V  | Vcc   |
| GND       | GND   |
| GPIO 12   | SCK   |
| GPIO 13   | DT    |

***Terminales de Conexión de ESP32-CAM a MOC3043***.
| ESP32-CAM | MOC3043 |
|-----------|---------|
| GPIO 15   | PIN 1   |
| GND       | PIN 2   |

2. Se tiene que fijar la celda de carga de 20Kg.en una base sólida que evite el desequilibrio de la báscula, cuidando la posición de la celda de carga, la cual suele tener una flecha que debe señalar hacia la base inferior, para su correcta colocación, véase figura.

![A028](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A028.PNG)

***Forma Física de la Celda de Carga de 20kg. Utilizada.***

3. Fijar la base de la colmena en la parte superior de la celda, teniendo un registro previo del peso total de la colmena para poder destarar y ajustar el valor correspondiente al peso registrado. Ver figuras

![A029](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A029.JPG)

***Vista frontal del acoplado de la celda de carga entre la base y la colmena.***

![A030](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A030.JPG)

***Vista diagonal del acoplado de la celda de carga entre la base y la colmena.***

4. Cargar el [programa](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Sensores_Temp_Humedad_Peso_MQTT/Sensores_Temp_Humedad_Peso_MQTT.ino) de control y adquisición de peso, temperatura y humedad.

![A031](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A031.JPG)

***Código de control cargado en el IDE de Arduino.***

5. Hasta el momento, en está parte del proyecto el circuito electrónico es capaz de detectar el peso de la colmena, la temperatura y humedad; al exterior y cercanas a la colmena. Para comprobarlo, se puede abrir el *Serial Monitor*, que es una herramienta integrada al IDE de Arduino, que nos permite observar los datos que mandemos a imprimir, en nuestro caso las variables de interés. La impresión de las variables están en formato JSON.


![A035](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A035.JPG)

***Observación de los datos impresos en el monitor serial del IDE de Arduino.***

Ya comprobada la adquisición y debido procesamiento de las variables, podemos comprobar la comunicación al Bróker Mosquitto, realizando una subscripción al tópico creado, desconectando el cable USB a USB mini, de la computadora y observando los valores que se imprimen en la consola.

![A036](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A036.JPG)

***Subscripción al tópico: codigoIoT/G7/Habeetat. Desde la consola de Ubuntu 20.04.***


![A037](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A037.JPG)

***Observación de la impresión de los valores en la consola de Ubuntu 20.04.***
 

### 2.	Activación de un actuador que funcione con 127Vca y hasta 1500W de potencia

Dentro de los requerimientos del proyecto Capstone, se solicita la activación de actuadores. En nuestro proyecto se decidió, utilizar la cámara implementada en el ESP32-CAM, para mandar una imagen de la colmena, como parte del reporte diario del estado de la colmena, o si así se requiere, se puede solicitar una imagen instantánea de la colmena, en el momento que el apicultor así lo decida; explicado en otro apartado del presente reporte. Para el segundo actuador, se decidió tener una etapa que permita controlar cargas de una alta potencia, hasta cerca de los 1500W (en comparación con el muy bajo consumo de potencia que tienen los microcontroladores, apenas de alrededor de 1W), y así poder activar un ventilador para regular un poco la temperatura cercana o interior a la colmena o activar una unidad que permita nebulizar algún medicamento para el control de las plagas o parásitos que atacan a las abejas.

Para el control de cargas de alta potencia se necesita implementar una etapa de acoplado, la cual se explica más a detalle en [Etapa de desacoplado](https://github.com/OmarAbundis/Etapa-de-desacoplado-con-MOC-y-TRIAC-para-activacion-de-carga-a-127Vca).

En la siguiente imagen se muestra una representación del circuito electrónico de desacoplado y activación de carga interactuando con un microcontrolador ESP32-CAM.

![A032](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A032.jpg)

***Representación del circuito de desacoplado y control.***

En la siguiente figura, se muestra ya el circuito armado e interconectado a los sensores DHT11, HX711, FTDI y el ESP32-CAM; ya como parte del circuito de control.

![A033](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A033.JPG)

***Circuito electrónico armado y listo para su funcionamiento***

En la siguiente figura, se muestra un ventilador (reciclado de un horno de microondas), como elemento actuador conectado a la etapa de acoplado y ya conectado al suministro eléctrico de 127Vca, a la espera de la señal de control.

![A034](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A034.JPG)

***Conexión del actuador al suministro eléctrico y el circuito de control.***

¡Listo! Ya se puede seguir avanzando en el escalado del proyecto.

## 3. Implementación de una base de datos en MySQL para llevar un registro de las variables detectadas

Hasta este momento, se tiene resuelto la detección de las variables de interés, peso de la colmena, temperatura y humedad ambientales cercanas a la colmena y la activación de un actuador que se pueda conectar al suministro eléctrico (127 Vca a 60Hz, estándar en México), pero todavía le faltan más implementaciones para que sea considerado como parte del ecosistema del Internet de las cosas. Por ejemplo, ya desde hace mucho tiempo si estas subscrito a alguna plataforma de *streaming*, habras notados que entre más haces uso de ella empieza después de un determinado tiempo, a sugeriste temas de tú interés, aunque tú no hayas empezado alguna búsqueda. ¿Cómo se realiza?

Estos sistemas de *streaming*, además de que tienen modelos de predicción o algoritmos de inteligencia artificial (que también se incluye en nuestro proyecto un ejemplo de implementación), para que funcionen necesitan de datos y entre más tiempo este recopilando datos, se puede hacer una mejor predicción, en el caso de los *streaming*, de tus gustos.

En resumen, para implementar un modelo predictivo, entonces necesitamos recopilar datos, provenientes del peso, temperatura, humedad y CO2; de la colmena y almacenarlos para su posterior procesamiento con algún algoritmo de predicción..

A continuación, se muestra, cómo se puede implementar una rápida y sencilla base de datos utilizando MySQL, que es un software libre y que fácilmente se puede implementar en Ubuntu 20.04, nuestro sistema operativo en utilización.

**Nota:** No olvide estudiar las referencias indicadas, ya que ahí se describe como instalar MySQL en Ubuntu 20.04.

Estos son los pasos por seguir:

1.	Ya teniendo instalado MySQL, en la consola de Ubuntu 20.04, escribe el comando
~~~
sudo mysql
~~~
Te solicitará tu contraseña, la escribes sin preocuparte de que no se muestre, es por seguridad, pulsa ENTER e ingresaras a MySQL.

![A038](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A038.JPG)

**Imagen de la consola cuando ya accedió a MySQL.**

2.	Creas una base de datos

CREATED DATABASE “Nombre que quieres para tu base de datos”;

Ejemplo:
~~~
CREATED DATABASE Habeetat_SensoresExt
~~~

3.	Corrobora su creación con el comando
~~~
SHOW databases;
~~~~

![A039](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A039.JPG)

**Nombres de las bases de datos existentes en MySQL.**

4.	Seleccionas tu base de datos creada con el comando
~~~
USE Habeetat_SensoresExt;
~~~

![A040](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A040.JPG)

**Indicación de que cambió la base de datos que se tenía por defecto.**

5.	Creas una tabla que contenga los campos deseados
~~~
create table Habeetat_SExt (id INT (6) UNSIGNED AUTO_INCREMENT PRIMARY KEY, fecha TIMESTAMP DEFAULT CURRENT_TIMESTAMP, Nombre CHAR (248) NOT NULL, Temperatura FLOAT (4,2), Humedad INT (3), Peso INT (4));
~~~
6.	Para comprobar usas el comando
~~~
select * from Habeetat_SExt;
~~~
Y te mostrará tu tabla con los campos creados.

![A041](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A041.JPG)

**Escritura de comando en la consola de Ubuntu 20.04**

![A042](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A042.JPG)

**Ejemplo de la tabla con datos ya almacenados.**

7.	Ahora a darle privilegios.

Si por ejemplo

Usuario es: PanchoLopez

Password es: 1234

El comando quedaría como

~~~
CREATE USER ‘PanchoLopez’@’localhost’ IDENTIFIED BY ‘1234’;
~~~
inmediatamente después,

~~~
GRANT ALL PRIVILEGES ON *.* TO ‘PanchoLopez’@’localhost’;
~~~

***Nota***: Guarda bien el usuario y la contraseña para su posterior uso.

¡Listo! Ya está la base de datos para el almacenamiento de los parámetros conrrespondientes a la variables temperatura, humedad y peso de la colmena.

# 4. Interfaz gráfica y de control en NodeRed

Hasta el momento, ya está implementado el circuito electrónico de control, ya se detectan las variables de interés temperatura, humedad y peso acumulado de la colmena, ya se cuenta con transmisión de los datos en formato JSON utilizando Bróker Mosquitto y se tiene implementada una base de datos en MySQL, para generar el almacenamiento del registro de los datos de la variable; pero aún le faltan implementaciones. Le falta una interfaz gráfica en donde cualquier usuario pueda leer de una manera simple, precisa y exacta las variables de interés, le falta incluir algunas estructuras de control, para la activación de los actuadores y poder mandar alertas y mensajes sobre la salud de la colmena.

Para estás implementaciones previamente señaladas, se va a utilizar Node-Red, que es una herramienta de desarrollo basada en flujo para programación visual, que permite conectar dispositivos de hardware, API y servicios en línea.

A continuación se indica cómo se realiza la implementación.

1.	Ya teniendo instalado Node-Red, desde la consola de Ubuntu 20.04 se escribe el comando 

~~~
node-red
~~~

el cual pone en marcha la herramienta de desarrollo.

![A043](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A043.JPG)

**Inicialización de Node Red.**

2.	Ya puesta en marcha la herramienta, abra un navegador y escriba el comando

~~~
localhost:1880/
~~~

![A044](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A044.JPG)

**Ingreso a Node RED**

Y el entorno está listo para comenzar con el diseño de su *Flow*

![A045](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A045.JPG)

3.	Se recomienda importar el [Flow de Habeetat SensoresExt](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Node-Red/Habeetat_NodeRed_Grafana_Telegram_V2.json) para comprobar la solución planteada, y el flujo se observará de la siguiente manera.

![A046](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A046.JPG)

**Flow de control de Habeetat SensoresExt**

4.	En la página de NodeRed se hace desplegado del *Dashboard*, dando clic en el cuadrito con flecha en diagonal apuntando hacia arriba, y se desplegará la interfaz gráfica.

![A047](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A047.JPG)

**Apertura del Dashboard.**

5.	Ya todo en operación el *Dashboard* muestra de arriba hacia abajo y de izquierda a derecha el grupo muestra el registro de medidas en tiempo real que provienen de los sensores ya procesadas y transmitidas por el microcontrolador ESP32-CAM vía Wi-Fi, haciendo uso del Bróker Mosquitto. En el segundo grupo se muestra el histórico de los valores detectados y en la parte inferior se muestra de forma embebida las gráficas realizadas en Grafana (a continuación se explicará) con los datos guardados en la base de datos **Habeetat_SensoresExt** de MySQL.

![A048](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A048.JPG)

**Ejemplo de vista del Dashboard**

Y, ¿cómo se hace interactuar Grafana con Node Red para visualizar los datos gráficos?

## 5. Graficado de variables registradas en Grafana

La intención de nuestro proyecto es que todos los datos recopilados y almacenados sean fácilmente interpretables y que mejor si se visualizan de manera gráfica. Para ello hemos utilizado Grafana, que es un software libre que permite la visualización y el formato de datos ya recopilados desde una base de datos, como MySQL.

**Nota:** Se aconseja revisar el material de referencia indicado o se pueden consultar los siguientes vídeos realizador por el profesor del curso Hugo Vargas, en donde a detalle se explica cómo realizar la configuración, vinculado con una base de datos, el *Query* para el manejo de datos y el embebido de las gráficas en Node Red.

[Diplomado IoT - SIC-2022-G7 - Plataformas del IoT - Grafana](https://www.youtube.com/watch?v=4y-WazppL6U&list=PLPz4YNz_pz1UwKweh8bRR9uWFp7DYv9ca&index=42)

[Diplomado IoT - SIC-2022-G7 - Plataformas del IoT - Grafana: Insertar paneles](https://www.youtube.com/watch?v=r9HMQ4m5jYU&list=PLPz4YNz_pz1UwKweh8bRR9uWFp7DYv9ca&index=43)

[Diplomado IoT - SIC-2022-G7 - Plataformas del IoT - Grafana: Insertar paneles 2](https://www.youtube.com/watch?v=Xnm0O074qXE&list=PLPz4YNz_pz1UwKweh8bRR9uWFp7DYv9ca&index=44)

1. Activamos Grafana desde la consola de Ubuntu 20.04 con el siguiente comando

~~~
sudo /bin/systemctl start grafana-server
~~~

![A049](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A049.JPG)

***Comando para iniciar Grafana desde la consola de Ubuntu 20.04.***

2. Abrimos un explorador y escribimos:

~~~
localhost:3000/
~~~

3. Registramos nuestros datos en donde se solicita.

![A050](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A050.JPG)

***Inicialización de Grafana.**

4. Elegimos la base de datos a utilizar.

![A051](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A051.JPG)

***Elección de la base de datos.***


5.	Ya habiendo realizado toda la configuración, vinculación de la base de datos y elegido el tipo de gráfico que mejor se ajusta para el desplegado histórico de los datos recopilados, se procede a escribir los *query* correspondientes.

**Query de temperatura**

~~~
SELECT
  fecha AS "time",
  Temperatura
FROM Habeetat_SensoresExt.Habeetat_SExt
ORDER BY fecha
~~~

![A052](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A052.JPG)

***Configuración de Query de Temperatura.***

**Query de Humedad**

~~~
SELECT
  fecha AS "time",
  Humedad
FROM Habeetat_SensoresExt.Habeetat_SExt
ORDER BY fecha
~~~

![A053](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A053.JPG)

***Configuración de Query de Humedad.***

**Query de Peso.**

~~~
SELECT
  fecha AS "time",
  Peso
FROM Habeetat_SensoresExt.Habeetat_SExt
ORDER BY fecha
~~~

![A054](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A054.JPG)

***Configuración de Query de Peso.***

6.	Se aplican y se salvan todas las configuraciones hechas.

![A054](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A054.JPG)

***Aplicación de configuraciones.***

![A055](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A055.JPG)
![A056](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A056.JPG)
![A057](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A058.JPG)

***Gráficos correspondientes a los Query configurados.***

7.	Se busca y se copia la ***Embed HTML*** para incrustarla en Node RED

![A058](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A058.JPG)

***Panel.***

8.	Se configura el nodo HTML

![A059](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A059.JPG)

***Nodo HTML.***

9.	Se realiza ***Deploy***

![A060](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A060.JPG)

***Ejecución de Deploy.***

10.	Y queda lista la incrustación en el *Dasboard*.

![A061](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/A061.JPG)

***Dasboard con gráficos incrustados.***

Y se ha completado el *Dasboard* para visualizar los valores de las variables que ayudan a verificar la salud de la colmena.


## Instrucciones de operación

## Resultados

## Evidencias

## Preguntas frecuentes

## Compatibilidad

## Créditos
