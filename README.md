# Habeetat: Colmena saludable

## Introducción

Como parte de las actividades del curso de internet de las cosas (IoT), implementado en la plataforma de [edu.codigoiot.com](https://www.codigoiot.com/), se solicita a manera de conclusión realizar un proyecto en donde se ponga en práctica lo aprendido a lo largo del curso e invita participar en lo que se denomina el [proyecto Capstone](https://edu.codigoiot.com/mod/resource/view.php?id=3463).

Dentro de los requisitos se busca que el proyecto repercuta en el desarrollo de la sociedad mediante el uso de las tecnologías de la comunicación y de ahí, el primer problema a resolver, ¿qué diseñar?

Teniendo en cuenta que hoy en día puedes encontrar hasta [cafeteras controladas por internet](https://www.home-connect.com/es/es/electrodomesticos-inteligentes/cafetera), no deberíamos tener problemas para elegir algo que realizar, pero nuevamente no se trata de conectar cualquier electrodoméstico a internet, sino que el proyecto sirva de **piedra angular** para el desarrollo de una área social y considerando que algo sobra en nuestro país, México, son problemas sociales.

Ya discutiendo como equipo y consultando las bases requeridas del proyecto, nos llamó la atención el monitoreo de la flora y la fauna, aspectos en los cuales nuestro país es rico (por el momento), pero también sumamente descuidado en realizar una explotación sustentable. Y dentro las muchas especies que se pueden monitorear, nos decidimos por las abejas.

**¿Por qué las abejas?**

Siguiendo con la discusión en equipo del proyecto, coincidimos que en muchas ocasiones en viajes a regiones propicias para la práctica de la apicultura, muchos habitantes de esas regiones combinan sus labores del campo con la práctica de la apicultura, simplemente siguiendo las enseñanzas heredadas y en muchas de ellas simplemente destinadas al fracaso, ya que solamente realizado el **cajón** utilizado como colmena, las dejan estar ahí acumulando la miel, pero realmente sin preocuparse de la salud de la colmena y por las observaciones hechas, pues prácticamente sin preocuparse del entorno que rodea a la colmena.

Así que decidimos buscar una solución mediante el uso del IoT que garantice la salud de la colmena.

**¿De qué manera?**

Dentro de las malas prácticas de los apicultores novatos o simplemente aficionados, notamos que principalmente descuidan la temperatura, la humedad y el uso de los pesticidad o hierbicidas; cercanos a la colmena o ataques de hormigas (arrieras), avispas u otros depredadores que un breve momento pueden terminar con el enjambre de la colmena y que decir, de los incendios forestales intencionales o no intencional, que también acaban en un instante con las colmenas.

Así que para el desarrollo del proyecto nos dimos a la tarea de **monitorear** las principales variables que nos alertaran que la salud de la colmena está en franco peligro, y estás son:

- Peso de la colmena.
- Temperatura exterior e interior.
- Humedad exterior e interior.
- Presencia de la concentración de CO2.

Llevar un **registro** de los valores detectados mediante la implementación de una base de datos en MySQL.
Si en el registro y monitoreo de las variables se detectan valores atípicos o de riesgo mandar señales a actuadores para que se pongan en funcionamiento y regulen la variable que se encuentra en estado crítico o en caso de emergencia se detone una **llamada de alerta** a la persona propietaria o encargada de la colmena.

Simplificar la **observación de los datos** mediante gráficas en tiempo real haciendo uso de Grafana y con todos los datos obtenidos, utilizar algoritmos de predicción que ayuden a diagnosticar que si las condiciones presentes seguirán manteniendo la salud o propiciarán la enfermedad de la colmena.
