## Introducción

Como parte de las actividades del curso de internet de las cosas (IoT), implementado en la plataforma de [edu.codigoiot.com](https://www.codigoiot.com/), se solicita a manera de conclusión realizar un proyecto en donde se ponga en práctica lo aprendido a lo largo del curso e invita participar en lo que se denomina el [proyecto Capstone](https://edu.codigoiot.com/mod/resource/view.php?id=3463).

Dentro de los requisitos se busca que el proyecto repercuta en el desarrollo de la sociedad mediante el uso de las tecnológias de la comunicación y de ahí, el primer problema a resolver, ¿qué diseñar?

Teniendo en cuenta que hoy en día puedes encontrar hasta [cafeteras controladas por internet](https://www.home-connect.com/es/es/electrodomesticos-inteligentes/cafetera), no deberíamos tener problemas para elegir algo que realizar, pero nuevamente no se trata de conectar cualquier electrodoméstico a internet, sino que el proyecto sirva de **piedra angular** para el desarrollo de una área social y considerando que algo sobra en nuestro país, México, son problemas sociales.

Ya discutiendo como equipo y consultando las bases requeridas del proyecto, nos llamó la atención el monitoreo de la flora y la fauna, aspectos en los cuales nuestro país es rico (por el momento), pero también sumamente descuidado en realizar una explotación sustentable. Y dentro las muchas especies que se pueden monitorear, nos decidimos por las abejas.

¿Por qué las abejas?

Siguiendo con la discusión en equipo del proyecto, coincidimos que en muchas ocasiones en viajes a regiones propicias para la práctica de la apicultura, muchos habitantes de esas regiones combinan sus labores del campo con la práctica de la apicultura, simplemente siguiendo las enseñanzas heredadas y en muchas de ellas simplemente destinadas al fracaso, ya que solamente realizado el **cajón** utilizado como colmena, las dejan estar ahí acumulando la miel, pero realmente sin preocuparse de la salud de la colmena y por las observaciones hechas, pues prácticamente sin preocuparse del entorno que rodea a la colmena.

Así que decidimos buscar una solución mediante el uso del IoT que garantice la salud de la colmena.

¿De qué manera?

Dentro de las malas prácticas de los apicultores novatos o simplemente aficionados, notamos que principalmente descuidan la temperatura, la humedad y el uso de los pesticidad o hierbicidas; cercanos a la colmena o ataques de hormigas (arrieras), avispas u otros depredadores que un breve momento pueden terminar con el enjambre de la colmena y que decir, de los incendios forestales intencionales o no intencional, que también acaban en un instante con las colmenas.

Así que para el desarrollo del proyecto nos dimos a la tarea de **monitorear** las principales variables que nos alertaran que la salud de la colmena está en franco peligro, y estás son:

- Peso de la colmena.
- Temperatura exterior e interior.
- Humedad exterior e interior.
- Presencia de la concentración de CO2.

Llevar un **registro** de los valores detectados mediante la implementación de una base de datos en MySQL.
Si en el registro y monitoreo de las variables se detectan valores atípicos o de riesgo mandar señales a actuadores para que se pongan en funcionamiento y regulen la variable que se encuentra en estado crítico o en caso de emergencia se detone una **llamada de alerta** a la persona propietaria o encargada de la colmena.

Simplificar la **observación de los datos** mediante gráficas en tiempo real haciendo uso de Grafana y con todos los datos obtenidos, utilizar algoritmos de predicción que ayuden a diagnosticar que si las condiciones presentes seguirán manteniendo la salud o propiciarán la enfermedad de la colmena.

En lo que respecta a la solución planteada, en esta parte del proyecto se muestra y decribe cómo realizar:

- La adquisición de la temperatura, humedad y peso.
- Implementación de una base de datos en MySQL para llevar un registro de las variables.
- Interfaz gráfica y de control en NodeRed.
- Graficado de variables registradas en Grafana.
- Activación de un actuador que funcione con 127Vca.
- Envío de mensaje de alerta por Telegram.
- Solicitud de estado de las condiciones de las variables en tiempo real por mensaje en Telegram.

A continuación se describen las distintas soluciones.

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

## Instrucciones para realizar el control del circuito de sensado de variables

**Nota:** Se recomienda revisar la información previamente citada, antes de comenzar con el armado del circuito electrónico, para reducir la probabilidad de realizar malas conexiones entre los dispositivos, fallas en la polarización y en consecuencia el daño permanente de los dispositivos o daño parcial o total de su equipo de cómputo.

1.  Se debe de armar el circuito electrónico mostrado en la figura 1, teniendo cuidado de conectar a las terminales indicadas del ESP32-CAM, y cuidar la polaridad de los dispositivos.

**Figura 1.** *Circuito Electrónico de Control y Adquisición de Peso, Temperatura y Humedad, y Control de Carga*.

![Circuito de control](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/Circuito%20de%20control%20de%20peso_temperatura%20humedad%20y%20carga.png)

En la tabla 1, se puede observar la correspondencia de las terminales que se deben de conectar entre el ESP32-CAM y el DHT11.

**Tabla 1.** *Terminales de Conexión de ESP32-CAM a DHT11*.

| ESP32-CAM | DTH11|
| ----------|------|
| GPIO 2    | DATA |
| 5V        | Vcc  |
| GND       | GND  |

En la tabla 2, se puede observar la correspondencia de las terminales que se deben de conectar entre el ESP32-CAM y el HX711.

**Tabla 2.** *Terminales de Conexión de ESP32-CAM a HX711*.

| ESP32-CAM | HX711 |
|-----------|-------|
| Vcc = 5V  | Vcc   |
| GND       | GND   |
| GPIO 12   | SCK   |
| GPIO 13   | DT    |

En la tabla 3, se puede observar la correspondencia de las terminales que se deben de conectar entre el ESP32-CAM y el MOC3043.

**Tabla 3.** *Terminales de Conexión de ESP32-CAM a MOC3043*.

| ESP32-CAM | MOC3043 |
|-----------|---------|
| GPIO 15   | PIN 1   |
| GND       | PIN 2   |

2. Se tiene que fijar la celda de carga de 20Kg.en una base sólida que evite el desequilibrio de la báscula, cuidando la posición de la celda de carga, la cual suele tener una flecha que debe señalar hacia la base inferior, para su correcta colocación, véase figura 2.

**Figura 2.** *Forma Física de la Celda de Carga de 20kg. Utilizada.*

![Celda de Carga](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Imagenes/Celda%20de%20carga.PNG)

3. Fijar la base de la colmena en la parte superior de la celda, teniendo un registro previo del peso total de la colmena para poder destarar y ajustar el valor correspondiente al peso registrado.
4. Cargar el [programa](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_Peso/Sensores_Temp_Humedad_Peso_MQTT/Sensores_Temp_Humedad_Peso_MQTT.ino) de control y adquisición de peso, temperatura y humedad.

## Instrucciones de operación

## Resultados

## Evidencias

## Preguntas frecuentes

## Compatibilidad

## Créditos
