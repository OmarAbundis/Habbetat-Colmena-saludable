# Creación del dashboard en grafana para mostrar los datos del interior de la colmena

## Resumen

En este repositorio se muestra el procedimiento para la creación del dashboard de Grafana en los que se muestran los datos recopilados con los sensores MQ135 y DHT11 para monitorear la temperatura, humedad y concentración de CO2 al interior de la colmena. El dashboard de grafana usa como fuente de datos la base de datos creada en el repositorio [Base_de_datos_My_SQL_interior_colmena](https://github.com/OmarAbundis/Habeetat-Colmena-saludable/tree/main/Control_Sensores_Temp_Hum_CO2_Interior/Base_de_datos_My_SQL_interior_colmena). El panel final consta de 3 gráficas de series de tiempo mostrando la temperatura, humedad y concentración de CO2 históricos y 3 indicadores de aguja que muestran los datos actuales de la variables medidas. Estas gráficas proporcionan un resumen gráfico muy vistoso de lo que ocurre al interior de la colmena.  

# Software necesario

* Máquina virtual con Ubuntu 22.04
* Grafana

# Instrucciones de instalación

1. Abrir una terminal de Ubuntu y teclear las siguientes instrucciones

+ `sudo apt-get install -y apt-transport-https` 
+ `sudo apt-get install -y software-properties-common wget`
+ `sudo wget -q -O /usr/share/keyrings/grafana.key https://packages.grafana.com/gpg.key`
+ `echo "deb [signed-by=/usr/share/keyrings/grafana.key] https://packages.grafana.com/enterprise/deb stable main" | sudo tee -a /etc/apt/sources.list.d/grafana.list`
+ `sudo apt-get update`
+ `sudo apt-get install grafana-enterprise`

2. Una vez terminada la instalación hay que arrancar Grafana y poder abrirlo desde el navegador, este comando se ejecuta cada vez que queramos abrir Grafana

* `sudo /bin/systemctl enable grafana-server`

3. Para abrir Grafana abrimos un navegador y nos vamos a la dirección `http://localhost:3000/` donde nos logeamos con el usuario y contraseña por deafault, se recomienda actualizar esos datos.

- `User: admin`
- `Password: admin`

Con lo anterior podemos crear ya un panel de Grafana

# Instrucciones de uso

1. Antes de comenzar a crear un panel de Grafana debemos añadir una fuente de datos (Add your first data source o add data source), para este panel elegimos MySQL en la lista de opciones de la que disponemos. 
2. Posteriormente le coolocamos un nombre a nuestra fuente.
3. El host es `localhost:3306`
4. El nombre de la base de datos debe ser el nombre con el que creamos la base: en este caso `sensor_MQ_DHT`
5. El usuario y contraseña con la que ingresamos a MySQL
6. Todas las demás opciones las dejamos por default
7. Oprimimos `Save & test`
8. Si todo está bien aparecerá un mensaje indicando que se agregó la base de datos
9. Agregamos un nuevo panel oprimiendo el botón superior derecho que contiene un símbolo de + y una gráfica de barras (`Add panel`)
10. Configuramos el panel
  * Eligiendo un tipo de gráfica (Time series, Bar chart, stat, gauge, table, heatmap, etc)
  * Elegimos la fuente de datos (data source)
  * Seleccionamos la columnas de nuestra base de datos a graficar
    * Seleccionar tabla
    * Seleccionar columna de tiempo  
    * SELECT column value (datos de temperatura, VoltajeAnalógico, Humedad)
    * En estas opciones se seleccionan todos los datos a mostrar en nuestra gráfica

<p align="center">
<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/Raymundo_dashborad_query_graf_24.jpg" />
</p>

    * Posteriormente se la da formato al gráfico para seleccionar colores, tipo de líneas, etiquetas a mostrar, etc
    * Oprimimos Apply
    
 <p align="center">
<img src="https://github.com/OmarAbundis/Habeetat-Colmena-saludable/blob/main/Control_Sensores_Temp_Hum_CO2_Interior/imagenes_interior/raymundo_grafana_25.jpg" />
</p>
    
    * La gráfica queda guardada y lista para ser mostrada
11. Se repiten los pasos anteriores para agregar nuevas gráficas a nuestro dashboard
12. Se guardan los cambios del panel 
13. Si se desea se puede exportar el panel en formato HTML para embeberlo en páginas web 



# Resultados




