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
    • IDE de Arduino 1.8.19
    • Drivers (Windows) para el esp32 cam (se comparte en el material semanal)
    • Bibliotecas de Arduino para el manejo del esp32 CAM
        ◦ https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json  (en preferencias-- Gestor de URLS)
        ◦ Instalar en el <gestor de tarjetas del IDE de Arduino> la tarjeta ESP32 de Expressif Systemas
        
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
# Servicios
- [Telegram bot API](https://core.telegram.org/bots/api)


# Instrucciones para construir el circuito del ESP32 CAM
El circuito a crear es el siguiente

<p align="center">
<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_ESP32_CAM_19.jpg" width="700" height="400" />
</p>


# Instrucciones para programar el ESP32 CAM

Para poder visualizar las imágenes y vídeo capturadas con la cámara del ESP32 CAM es necesario crear un servidor web, el procedimiento descrito a continuación nos permitirá crear el servidor web para visualizar en un navegador y en Python las imágenes y vídeo.
1. Descargar e Instalar el IDE de Arduino 1.18.19 de la página oficial   https://www.arduino.cc/en/software

2. Instalar los drivers para establecer la conexión serial entre el circuito de la ESP32 CAM y la computadora. Los drivers son los CH34x para Windows. Si se instala en Linux no es necesario instalarlos ya que vienen por default.

3. Dar de alta la tarjeta ESP32 cam en el IDE de Arduino en el menú archivo >> preferencias y el campo de gestor de URLS adicionales escribir 
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json 

4. En el IDE de Arduino ir a Herramientas>> Placa >> Gestor de tarjetas, buscar la placa ESP32 CAM de Expressiff Systems e instalarla. En caso de que no aparezca la placa revisar el paso anterior. 

5. Después de instalar la tarjeta hay que elegir la placa ESP32 de AI Thinker para poder programarla, se elige en el menú herramientas >> placa >> ESP32 arduino >> AI Thinker ESP32-CAM. Al finalizar hay que conectar la placa al puerto USB.

6. Una vez configurada la placa se debe revisar que haya comunicación serial entre el dispositivo y la computadora, por lo que hay que tener conectada el ESP32 a la computadora, para esto hay que ir al menú herramientas >> monitor serie. Otra forma de saber si hay comunicación es revisar si hay puerto disponible en el menú >> puerto, si aparece un puerto habilitado es indicio de que hay comunicación. Al momento de revisar la comunicación con la primera opción hay que colocar la velocidad del monitor serial en 9600 o 115600 baudios para obtener texto que indique la comunicación. Dado que estamos usando la placa ESP32 con el convertidor usb-ttl sólo es necesario oprimir el botón de download o reset para saber si está comunicándose con la computadora.

7. Establecida la comunicación serial entre el ESP32 y la computadora procedemos a cargarle el programa que nos permite crear el servidor web para tomar imágenes y vídeo, para esto usaremos el programa de la carpeta [Control_Camar_Video](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/tree/main/Control_Camara_Video/Servidor_Web_ESP32_CAM_Colmena)


# Notas del uso del programa del ESP32 CAM y del flow de node red
# Resultados
# Evidencias
# Preguntas frecuentes 
# Compatibilidad
## Créditos
Este proyecto se realizó gracias al apoyo de los profesores
- Lizbeth García León [Github](https://github.com/lizgarcialeon)
- Hugo Escalpelo [Github](https://github.com/hugoescalpelo/detector-sintomas-covid)
- Omar Abundis Noyola [Github](https://github.com/OmarAbundis)
- Raymundo Soto Soto [Github](https://github.com/raymundosoto)



