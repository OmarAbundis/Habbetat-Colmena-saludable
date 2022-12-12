# Predicción del peso de la colmena usando Prophet

<p align="center">
<img src="https://miro.medium.com/max/964/0*tVCene42rgUTNv9Q.png"  />
</p>


# Resumen

En este módulo se realizó la programación del predictor del peso de la colmena usando una herramienta de predicción de series de tiempo desarrollada por Facebook denominada *Prophet*. Esta biblioteca permite predecir el comportamiento de series de tiempos que tengan componentes periódicos históricos, comportamientos no lineales e incluso que presenten vacíos en sus datos. Por lo anterior es el modelo adecuado para nuestro conjunto de datos. El programa nos crea varias gráficas que permiten verificar los datos históricos, las líneas de tendencia y la predicción hacía adelante de los periodos de tiempo que elijamos.     

# Material necesario

No requiere material físico, sólo se requiere el [conjunto de datos que se usarán para predecir el peso](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Prediccion_Peso_Colmena/abejas_datos.csv)

# Software a utilizar

* El software se ejecuta en una máquina virtual de virtual box en donde se corre Ubuntu 20.04 revisar la [guía de creación de máquinas virtuales](https://github.com/codigo-iot/Notas-de-clase/blob/main/IoT-SIC-G7/20220512%20-%20VirtualBox)
* Anaconda para linux [Guía de instalación de Anaconda en linux](https://docs.anaconda.com/anaconda/install/linux/) 
* [Python 3.8.0](https://www.python.org/downloads/release/python-380/)
* [Flow de Nodered del proyecto Habeetat](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/tree/main/Control_Sensores_Temp_Hum_CO2_Interior/Flow_Nodered_monitoreo_interior_colmena)
* [Cron para linux](http://dis.um.es/~lopezquesada/documentos/IES_1213/SAD/curso/UT3/ActividadesAlumnos/13/cron.html)

# Material de referencia

Para correr el script se recomienda crear un ambiente virtual de Python que corra en Anaconda y que ejecute en Python 3.8.0 [Guía de creación y gestion de ambientes virtuales en Ancaonda](https://conda.io/projects/conda/en/latest/user-guide/tasks/manage-environments.html)

# Servicios
En esta parte del proyecto Habeetat se hace uso de Telegram para recibir y enviar mensajes de la predicción del peso de la colmena

* [Telegram bot API](https://core.telegram.org/bots/api)
* Crear y configurar el bot de telegram en la aplicación usando esta [Guía de configuración del bot de telegram](https://www.adslzone.net/como-se-hace/telegram/crear-bot/)

# Instrucciones de instalación

# Instrucciones de uso del programa

# Resultados

# Evidencias

# Preguntas frecuentes

# Compatiblidad

El programa se realizó en Python 3.8.0 pero es comptible con versiones más nuevas de Pythonexith() 

# BIbliografía

Para el uso e implementación del algoritmo de predicción _Prophet_ revisar el siguiente articulo

1. Taylor, S. J., & Letham, B. (2018). Forecasting at scale. The American Statistician, 72(1), 37-45. [Link](file:///D:/Descargas%202022/peerj-preprints-3190.pdf)

# Créditos

Este proyecto se realizó gracias al apoyo de los profesores

- Lizbeth García León [Github](https://github.com/lizgarcialeon)
- Hugo Escalpelo [Github](https://github.com/hugoescalpelo/detector-sintomas-covid)
- Omar Abundis Noyola [Github](https://github.com/OmarAbundis)
- Raymundo Soto Soto [Github](https://github.com/raymundosoto)
