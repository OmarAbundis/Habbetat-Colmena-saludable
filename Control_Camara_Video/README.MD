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
- [IDE de Arduino 1.8.20](https://www.arduino.cc/en/software)
- [NodeRed v3.0.2](https://nodered.org/)

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

Imagen 
# Instrucciones para programar el ESP32 CAM
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



