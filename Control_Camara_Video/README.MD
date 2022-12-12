# Resumen
En esta sección del proyecto Habeetat se construye el modulo que se encarga del envío de imágenes y vídeo en tiempo real al flow de NodeRed donde, posteriormente, son enviadas al chat de Telegram para su consulta. El módulo consiste de un microcontrolador ESP32 con cámara que se conecta al Wifi y funciona como un servidor web de imágenes y vídeos, esto permite el intercambio de imágenes a través de internet. El bot de telegram se configura de tal forma que en un chat se pueda hacer la petición de las imágenes en tiempo real enviando la palabra _imagen_. Al final se muestran imágenes de su funcionamiento. 
# Material necesario
1.	Computadora
2.	1 microcontrolador ESP32 con cámara OV2640
3.	1 Modulo adaptador FTD232RL FTD USB a TTL
4.	1 Protoboard
5.	Cables jumper MM
6.	1 cable miniusb a USB
# Software a utilizar

El software se instalará en la computadora donde conectaremos nuestro ESP32 CAM.
Respetar la versión del software que se indica para evitar conflictos entre las bibliotecas.  
 * IDE de Arduino 1.8.19
 * NodeRed
 * Nodos de Nodered a usar (instalarlos desde nodered)
  * [Image tools](https://flows.nodered.org/node/node-red-contrib-image-tools)  
  * [mySQL](https://flows.nodered.org/node/node-red-contrib-image-tools)
  * [Telegrambot](https://flows.nodered.org/node/node-red-contrib-telegrambot)
        
Bibliotecas de Arduino para programar el ESPCAM y convertirlo en un servidor web de imágenes (todas están incluidas en la biblioteca estándar del IDE de Arduino
- esp_camera
- WiFi
- esp_timer
- img_converters.
- fb_gfx
- soc/soc   Biblioteca que deshabilita los problemas de brownout
- soc/rtc_cntl_reg   Biblioteca que deshabilita los problemas de browout
- esp_http_server

# Material de referencia
    
- [Instalación de NodeRed](https://github.com/hugoescalpelo/Notas-de-clase/blob/main/IoT-SIC-G7/20220531%20-%20Instalacion%20de%20NodeRed)
    
- [Instalación de IDE Arduino](https://github.com/hugoescalpelo/Notas-de-clase/blob/main/IoT-SIC-G7/20220714%20-%20Configuracion%20de%20la%20IDE%20de%20Arduino%20para%20ESP32)
    
# Servicios
- [Telegram bot API](https://core.telegram.org/bots/api)
- Crear y configurar el bot de telegram en la aplicación usando esta [Guía de configuración del bot de telegram](https://www.adslzone.net/como-se-hace/telegram/crear-bot/)
    


# Instrucciones para construir el circuito del ESP32 CAM
El circuito a crear es el siguiente

<p align="center">
<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_ESP32_CAM_19.jpg" width="700" height="400" />
</p>

La conexión entre pines del FTD y el ESP32 CAM; debe ser el siguiente:
| ESP32 CAM |FTDI  |
|--|--|
|5V  |5V  |
|GND  |GND  |
| UOT |RX  |
|UOR  |TX  |

# Instrucciones para programar el ESP32 CAM

Para poder visualizar las imágenes y vídeo capturadas con la cámara del ESP32 CAM es necesario crear un servidor web, el procedimiento descrito a continuación nos permitirá crear el servidor web para visualizar en un navegador las imágenes y vídeo.
1. Descargar e Instalar el IDE de Arduino 1.18.19 de la página oficial   https://www.arduino.cc/en/software

2. Instalar los drivers para establecer la conexión serial entre el circuito de la ESP32 CAM y la computadora. Los drivers son los CH34x para Windows. Si se instala en Linux no es necesario instalarlos ya que vienen por default.

3. Dar de alta la tarjeta ESP32 cam en el IDE de Arduino en el menú archivo >> preferencias y el campo de gestor de URLS adicionales escribir 
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json 

4. En el IDE de Arduino ir a Herramientas>> Placa >> Gestor de tarjetas, buscar la placa ESP32 CAM de Expressiff Systems e instalarla. En caso de que no aparezca la placa revisar el paso anterior. 

5. Después de instalar la tarjeta hay que elegir la placa ESP32 de AI Thinker para poder programarla, se elige en el menú herramientas >> placa >> ESP32 arduino >> AI Thinker ESP32-CAM. Al finalizar hay que conectar la placa al puerto USB.

6. Una vez configurada la placa se debe revisar que haya comunicación serial entre el dispositivo y la computadora, por lo que hay que tener conectada el ESP32 a la computadora, para esto hay que ir al menú herramientas >> monitor serie. Otra forma de saber si hay comunicación es revisar si hay puerto disponible en el menú >> puerto, si aparece un puerto habilitado es indicio de que hay comunicación. Al momento de revisar la comunicación con la primera opción hay que colocar la velocidad del monitor serial en 9600 o 115600 baudios para obtener texto que indique la comunicación. Dado que estamos usando la placa ESP32 con el convertidor usb-ttl sólo es necesario oprimir el botón de download o reset para saber si está comunicándose con la computadora.

7. Establecida la comunicación serial entre el ESP32 y la computadora procedemos a cargarle el programa que nos permite crear el servidor web para tomar imágenes y vídeo, para esto usaremos el programa de la carpeta [Control_Camara_Video](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/tree/main/Control_Camara_Video/Servidor_Web_ESP32_CAM_Colmena). El programa se cargará al editor de código de Arduino para posteriormente enviarlo al ESP32CAM
    
8. Antes de cargar el código a la tarjeta debemos definir el tipo de cámara que estamos usando (en nuestro caso es CAMERA_MODEL_AI_THINKER) y colocar el nombre de la red wifi y el password de la a que nos conectaremos con el ESP32 CAM.

**Antes de subir el código hay que cerciorrase que el GPIO del ESP32 CAM esté conectado a GND para entrar en el modo programador, después de subir el código habrá que desconectarlos**

![imagen](https://user-images.githubusercontent.com/72757419/207119299-ea247f1b-f0fa-4dc7-9887-429a59bd08c4.png)
    
9. Realizado lo anterior nos cercioramos que este conectado el ESP32 al puerto USB. Abrimos el monitor serial para revisar el status de la compilación y subida del código, oprimimos el botón de reset del ESP32 CAM una vez y subimos el código a la placa usando el botón subir. Esto comenzará a programar el ESP32, tardará unos segundos.
   
10. Al finalizar la programación del ESP32 en el monitor serial debemos ver un mensaje donde nos indicará la dirección donde podemos capturar imagen y vídeo

![imagen](https://user-images.githubusercontent.com/72757419/207119456-9ed2dea4-0d48-40cb-b43e-2c70d5c51b2d.png)
    
Del mensaje anterior nos interesa la última línea que nos informa la dirección IP donde podemos visualizar las imágenes de la cámara web del ESP32 CAM

     Camera Ready! Use ‘http://192.168.x.xx’ to connect

Copiamos y pegamos la dirección en un navegador web y ya tendremos listo nuestro servidor para recibir imágenes y vídeo del microcontrolador ESP32 CAM.
![imagen](https://user-images.githubusercontent.com/72757419/207119924-538f7ba7-3393-4469-8a62-cac5af6860c7.png)

# Notas del uso del programa del ESP32 CAM y del flow de node red

Esta parte del proyecto se usa en conjunto con el flow de nodered que se encuentra en la carpeta [Flow_Nodered_monitoreo_interior_colmena](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/tree/main/Control_Sensores_Temp_Hum_CO2_Interior/Flow_Nodered_monitoreo_interior_colmena)

Para poder visualizar las imágenes y el vídeo en tiempo real en el dashboard de nodered se deben usar nodos http request y template donde se coloquen los siguientes códigos HTML, recordar que http://192.168.x.xx es la dirección que nos arroja el monitor serial de arduino al momento de conectar el ESP32 

Para capturar fotografía
~~~~
<div style="margin-bottom: 10px;">
    <img src="http://192.168.x.xx:81/capture" width="1500px" height="750px">
</div>
~~~~

Para capturar vídeo
~~~~
<div style="margin-bottom: 10px;">
    <img src="http://192.168.x.xx" width="1500px" height="750px">
</div>
~~~~
<p align="center">
<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_env%C3%ADo_imagenes_04.jpg"  />
</p>

En el nodo http request la dirección a la que hacemos la petición será "http://192.168.x.xx:81/capture". Los nodos image y write file que se observan son para obtener una vista prevía de la imagen y guardar la imagen en una ruta específica donde los nodos de telegram buscarán la imágen para enviarla al hacer la petición de imagen.

La parte del flow que recibe la petición de *imagen* y envía una fotografía al chat de Telegram es la siguiente:

<p align="center">
<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_env%C3%ADo_imagen_05.jpg"  />
</p>

El nodo función *Envío imagen cámara Telegram* lleva el siguiente código

~~~~
if (msg.payload.content == "imagen" || msg.payload.content == "Imagen")
{
    msg.payload = {};
    msg.payload.chatId = -xxxxxxxxx; // Aquí va el ID del chat de telegram donde se publica el mensaje
    msg.payload.type = "photo";
    var espacio = " \n";
    msg.payload.content = "/ruta_a_la_imagen/imagenactual.png"; // Ruta hacía la imagen que se envía
    return msg;
}
~~~~

En este script hay que añadir el ID del chat de telegram hacía donde se envía la imagen y la imagen que se envirá específicando la ruta completa y el nombre de la imagen que en nuestro caso es *imagenactual.png*

# Resultados
Se muestra 


    <div class="fila">
        <div class="columna">
            <img src="[https://picsum.photos/800/600](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_imagen_06.jpg)">
        </div>
        <div class="columna">
            <img src="[https://picsum.photos/800/600](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_node_red_dashboard_08.jpg)">
        </div>
    </div>    
    </div>


# Evidencias
# Preguntas frecuentes 
# Compatibilidad
## Créditos
Este proyecto se realizó gracias al apoyo de los profesores
- Lizbeth García León [Github](https://github.com/lizgarcialeon)
- Hugo Escalpelo [Github](https://github.com/hugoescalpelo/detector-sintomas-covid)
- Omar Abundis Noyola [Github](https://github.com/OmarAbundis)
- Raymundo Soto Soto [Github](https://github.com/raymundosoto)



