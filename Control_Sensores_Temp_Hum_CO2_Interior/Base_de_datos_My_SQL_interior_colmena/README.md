## Creación de la base de datos MySQL para los datos del interior de la colmena

# Resumen

La base de datos se creo en una máquina virtual de Ubuntu 20.04 usando MySQL. Los datos obtenidos de los sensores MQ135 y DHT11 son enviados por MQTT en formato json al broker local donde son leìdos por el flow de NodeRed y guardados en nuestra base de datos local usando el nodo MySQL. Posteriormente está base de datos es usada com fuente de datos para un panel de Grafana donde visualizamos el comportamiento local.

# Instrucciones para creación de base de datos

1. Abrir una terminal e instalar mysql server con los comandos
* `sudo apt update`
* `sudo apt install mysql-server`
    
2. Ejecutar mysql
* `sudo mysql`
    
3. Crear una nueva base de datos para guardar los datos de los sensores
    `CREATE DATABASE sensor_MQ_DHT;`
    
4. Seleccionar base de datos
    `USE sennor_MQ_DHT;`
    
5. Crear una tabla llamada registro que contenga todos los campos necesarios
    `CREATE TABLE Datos_Sensores (n_registro INT(7) UNSIGNED AUTO_INCREMENT PRIMARY KEY, fecha TIMESTAMP DEFAULT CURRENT_TIMESTAMP, id_sensor CHAR (248) NOT NULL, ValorAnalogico FLOAT(7,3) NOT NULL, VoltajeAnalogico FLOAT(7,3) NOT NULL, Temperatura FLOAT(7,3) NOT NULL, Humedad FLOAT(7,3) NOT NULL);`
    
    Esto creará la base de datos que guardará nuestros datos que son
    * id_sensor
    * ValorAnalogico
    * VoltajeAnalogico
    * Tempertura
    * Humedad
