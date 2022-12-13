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

1. Copiar el contenido de este repositorio en una carpeta de nuestra máquina virtual, asegurarse que estén los siguientes archivos en la carpeta
*   abejas_datos.csv
*   prediccion_profeta.py
*   requirements.txt
2. Instalar Anaconda en la máquina virtual de Ubuntu 20.04
3. Abrir una terminal de linux en la carpeta donde guardamos los archivos del paso 1 y crear un ambiente virtual con Python 3.8 con la siguiente instrucción
~~~~
conda create -n profeta python=3.8
~~~~
En nuestra instalación el nombre del ambiente virtual es *profeta*

Se instalarán varios archivos y las dependencias, seleccionar _Y_ cuando lo lo pida la instalación.

4. Activar el ambiente virtual en la terminal tecleando
~~~~
conda activate profeta
~~~~
Esto activará nuestro ambiente y podremos usar Python 3.8 para ejecutar nuestro script.

5. Instalar *Prophet* y sus dependencias, para esto usaremos el archivo *requeriments.txt* del paso 1. Usar la siguiente instrucción
~~~~
pip install requeriments.txt
~~~~
La instrucción instalará todas las bibliotecas que están enlistadas en el archivos *requeriments.txt*, dentro de ellas está incluida *prophet 1.1.1* que es la que usamos en este trabajo. Al finalizar esta instlación ya podemos hacer predicción del comportamiento del peso de la colmena. 

6. Ejecutar el código *prediccion_profeta.py* para realizar la predicción con la siguiente instrucción
~~~~
python prediccion_profeta.py
~~~~
Al ejecutar el script se verá una ventana con la siguiente información

<p align="center">
<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_prediccion_19.jpg"  />
</p>

# Instrucciones de uso del programa

En nuestro proyecto todavía no tenemos datos reales que hayan sido medidos *in situ* para probar el modelo de predicción por lo que usamos un conjunto de datos reportados en la plataforma [kagle.com](https://www.kaggle.com/) de un proyecto denominado [beehive metrics](https://www.kaggle.com/datasets/se18m502/bee-hive-metrics) que contiene varios datasets reales con el peso de la colmena. De esta forma fue posible conseguir y usar los datos. 
1. Para ejecutar el código *prediccion_profeta.py* hay que tomar en cuenta las siguientes consideraciones:
* El archivo de datos a usar para la predicción debe tener extensión *.csv*
* El archivo debe contener 2 columnas, la primera debe tener el encabezado *ds* y la segunda *y*. La primera es la columna del tiempo (datestamp) y la segunda el peso.
* El conjunto de datos puede ser de *n* columnas (millones de datos).

2. La siguiente lìnea del código
~~~~
df = pd.read_csv('abejas_datos.csv')
~~~~
Lee el conjunto de datos *abejas_datos.csv* que está en la misma carpeta que el script, sino están en misma ubicación habrá que escribir la ruta completa.  

3. La línea de código
~~~~
df = df[-5000:]
~~~~
importa al espacio de trabajo los últimos 5000 datos del dataframe, con estos se realiza la predicción. Se puede modificar para considerar mayor cantidad de datos.

4. La elección del tiempo hacía adelante en el que queremos observar la predicción se realiza en la línea
~~~~
future = m.make_future_dataframe(periods=1)
~~~~
Donde periods es el parámetro que nos permite elegir cuántos días hacía adelante, si queremos más días de predicción considerar periods>1, con la salvedad que a mayor cantidad de días el error de la predicción aumenta.

5. Se recomienda elegir una mayor cantidad de datos para tener un comportamiento más exacto y que el error de predicción disminuya. 

# Automatización de la predicción con Cron

Cron es una aplicación de Linux/Unix diseñada para ejecutar automáticamente comandos y scripts en un momento concreto, a una hora y fecha establecidas. Puede ser utilizado para cualquier tarea, pero es usado sobre todo para respaldos y otras tareas administrativas. Cron viene instalado en Linux y por defecto se ejecuta automáticamente al iniciar el equipo por lo que sólo edita el tiempo en el que queremos que se ejecute la tarea.

Las tareas de Cron se registran y administran en un archivo especial llamado crontab. Cada perfil de usuario del sistema puede tener su propio crontab para programar tareas, que se almacenan en /var/spool/cron/crontabs.

Para programar una tarea, simplemente debe abrir su crontab a fin de editar y añadir una tarea escrita en forma de expresión de Cron. La sintaxis para escribir expresiones de Cron puede dividirse en dos elementos: la programación y el comando de ejecución.

El comando puede ser prácticamente cualquiera que ejecute habitualmente en la línea de comandos. El componente de programación de la sintaxis se divide en 5 campos distintos, que se escriben en el siguiente orden:
~~~~
minute hour day_of_month month day_of_week comandos_a_correr
~~~~
Si queremos saber si Crontab se está ejecutando en nuestro shell de linux tecleamos la instrucción `systemctl status cron` si el servicio está activo nos lo mostrará con la leyenda `active`. Si no está activo podemos ponerlo a trabajar con la instrucción `sudo service cron start`. Si queremos saber cuándo se ejecutó por última vez podemos usar `cron ps aux | grep cron`.

Para programar la ejecuciòn de nuestro script *prediccion_profeta.py* se realizan los siguientes pasos.

1. Abrir una terminal de Linux
2. Editar Crontab con el comando
~~~~
crontab -e
~~~~
Esto abrirá el editor de código predeterminado de Linux
3. Ir a la última línea del archivo y pegar la siguiente instrucción
~~~~
0 0 * * 1 conda activate profeta && python ruta_al_archivo/prediccion_profeta.py
~~~~
Despues de guardar los cambios y cerrar el archivo saldrá el mensaje `crontab: installing new crontab` que indica que se realizó el cambio satisfactoriamemnte.

Este comando realizará de forma automática la predicción al activar el ambiente virtual profeta y después ejecutará el script predicción_profeta.py todos los lunes a la media noche.
<p align="center">
<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_crontab__b_020.jpg" />
</p>

# Petición de predicción en el bot de Telegram 
Esta predicción trabaja en conjunto con el [flow de node red del proyecto Habeetat](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/tree/main/Control_Sensores_Temp_Hum_CO2_Interior/Flow_Nodered_monitoreo_interior_colmena) que permite obtener las gráficas con los resultados de la predicción. Para esto se agregaron 3 nodos: receiver, function y sender. El nodo sender y receiver se configuran con el nombre del bot creado y su token, el nodo receiver recibe la palabra *prediccion* y envía las gráficas al chat elegido usando el nodo función *Envío predicción Telegram 2*

<p align="center">
<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_chat_sender_telegram_02.jpg" />
</p>
El código para el nodo función *Envío predicción Telegram 2* que enviará un grupo de 3 imágenes con el resultado de la predicción es el siguiente.

~~~~
if (msg.payload.content == "prediccion" || msg.payload.content == "Prediccion")
{   
    msg.payload = {};
    msg.payload.chatId = -xxxxxxxxx, -xxxxxxxxx;
    msg.payload.type = "mediaGroup";
    msg.payload.content = [
    {
        type : "photo",
        media : "/home/raymundo/Documents/IOT/Archivos_proyecto/profeta/prediccion_1.png",
        caption : "Tendencia y predicción de los datos de las últimas horas"
    },
    {
        type : "photo",
        media : "/home/raymundo/Documents/IOT/Archivos_proyecto/profeta/analisis_tendencia.png",
        caption : "Análisis de temporalidad de los datos"
    },
    {
        type : "photo",
        media : "/home/raymundo/Documents/IOT/Archivos_proyecto/profeta/zonas_cambios.png",
        caption : "Análisis de los cambios más bruscos"
    }
];
return msg;   
}
~~~~

en msg.payload.chatId colocamos el chatId de los chats de telegram donde visualizaremos las gráficas de la predicción 


# Resultados
Las siguiente gráficas son el producto de la predicción: la primera gráfica representa el comportamiento histórico de los datos del peso de la colmena (puntos negros), la línea de tendencia predecida por el modelo *prophet*(línea azul) y la incertidumbre de la predicción (franja azul clara). Se muestra también una muestra del envío de la predicción al chat de Telegram
|  |  |
|--|--|
| ![Imagen 1](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Prediccion_Peso_Colmena/prediccion_1.png?raw=true) | ![Imagen 2](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Prediccion_Peso_Colmena/analisis_tendencia.png?raw=true) |
| ![Chat telegram](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Prediccion_Peso_Colmena/zonas_cambios.png?raw=true) |![enter image description here](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_prediccion_07.jpg?raw=true)

# Evidencias

Videos de YouTube

1. Funcionamiento de los sensores con MQTT, Nodered y la base de datos MySQL.

https://www.youtube.com/watch?v=seBQrWVgVqA

2. Funcionamiento del bot de Telegram

https://www.youtube.com/watch?v=s4fPHFBnQRI 

3. Panel de Grafana y Dashboard de Nodered

https://youtu.be/pgujhDJBkKk

# Preguntas frecuentes
P. ¿Se puede usar el programa sin necesidad de instalar el ambiente virtual de Anaconda?.

R. Si, se puede pero es una buena práctica crear los ambientes virtuales para ejecutar proyectos de este tipo para encapsular las dependencias y que no intereactuen con algunas otras instalaciones.

P. ¿Hay algunos otros modelos para predecir el comportamiento del peso de la colmena?

R. Sí, como mpor ejemplo las redes neuronales del tipo LSTM pero para este proyecto se eligió el modelo Prophet ya que es aconsejable para el tipo de datos que se obtienen con los sensores.

# Compatiblidad

El programa se realizó en Python 3.8.0 pero es compatible con versiones más nuevas de Pythonexith() 

# BIbliografía

Para el uso e implementación del algoritmo de predicción _Prophet_ revisar el siguiente articulo

1. Taylor, S. J., & Letham, B. (2018). Forecasting at scale. The American Statistician, 72(1), 37-45. [Link](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Prediccion_Peso_Colmena/Articulo_prediccion_prophet.pdf)

# Créditos

Este proyecto se realizó gracias al apoyo de los profesores

- Lizbeth García León [Github](https://github.com/lizgarcialeon)
- Hugo Escalpelo [Github](https://github.com/hugoescalpelo/detector-sintomas-covid)
- Omar Abundis Noyola [Github](https://github.com/OmarAbundis)
- Raymundo Soto Soto [Github](https://github.com/raymundosoto)
