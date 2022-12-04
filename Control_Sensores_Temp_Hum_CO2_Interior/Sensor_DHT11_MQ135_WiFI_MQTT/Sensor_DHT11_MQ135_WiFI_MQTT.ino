/*  
*  En este programa se conecta el controlador ESP32 DevKit 1
*  a los sensores MQ135 para medir la concentración de CO2 
*  y al sensor DHT11 para medir la temperatura y humedad dentro de la colmena
*  El esp32 se conecta a wifi y despues se conecta a un tópico del broker local mqtt
*  y publica los datos recogidos por los sensores, que posteriormente son leídos desde NodeRed
*  y guardados en una base de datos de MySQL que a su vez son leídos en Grafana para su visualizaciòn en un dashborad
*  Los datos del peso de la colmena son tratados para crear un modelo que prediga el peso en los días subsecuentes 
*  Parte de este programa fue realizado tomando como base el código del Ing. Hugo Escalpelo en el respositorio
*  https://github.com/hugoescalpelo/esp32cam-dht11-g7/tree/main/ESP32CAM-MQTT-JSON-DHT11
*/

//Bibliotecas
#include <WiFi.h>  // Biblioteca para el control de WiFi
#include <PubSubClient.h> //Biblioteca para conexion MQTT
#include <DHT.h> // Biblioteca para usar el sensor DHT11

// Datos Sensor DHT11
#define DHTTYPE DHT11   // Definimos sensor DHT 11
#define DHTPIN 14 //Pin digital conectado al DHT 11

DHT dht(DHTPIN, DHTTYPE);  // Iniciar sensor DHT11

//Datos de WiFi
const char* ssid = "TOTALPLAY_49C538";  // Aquí debes poner el nombre de tu red
const char* password = "T0T42W1WS1";  // Aquí debes poner la contraseña de tu red

//Datos del broker MQTT
const char* mqtt_server = "192.168.100.130"; // Se coloca la dirección IP de la computadora donde estamos trabajando
IPAddress server(192,168,100,130); // Se vuelve a escribir la dirección IP 

// Objetos
WiFiClient espClient; // Manejo de los datos de conexion WiFi
PubSubClient client(espClient); // Aquí se manejan los datos de conexion al broker

// Se declaran los pines del microcontrolador a usar 
int flashLedPin = 4;  // Para indicar el estatus de conexión
int statusLedPin = 33; // Para ser controlado por MQTT
long timeNow, timeLast; // Variables de control de tiempo no bloqueante
int data = 0; // Contador
int wait = 5000;  // Indica la espera cada 5 segundos para envío de mensajes MQTT




// Inicialización del programa
void setup() {
  // Se inicia la comunicación serial 115200 bits por segundo:
  Serial.begin(115200);
  
   //Resolución analógica a 12 bits (0-4096)
  analogReadResolution(12);             // Se usa una resoluciòn de 12 bits para realizar la lectura análogica del sensor MQ135
  Serial.println(F("Test del DHT11"));
  
  dht.begin(); // Función que inicia el sensor
  pinMode (flashLedPin, OUTPUT);
  pinMode (statusLedPin, OUTPUT);
  digitalWrite (flashLedPin, LOW);
  digitalWrite (statusLedPin, HIGH);

  Serial.println();
  Serial.println();
  Serial.print("Conectar a ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password); // Esta es la función que realiza la conexión a WiFi
 
  while (WiFi.status() != WL_CONNECTED) { // Este bucle espera a que se realice la conexión
    digitalWrite (statusLedPin, HIGH);
    delay(500); //se inicia una espera de conexón bloqueante
    digitalWrite (statusLedPin, LOW);
    Serial.print(".");  // Indicador de progreso de conéxion
    delay (5);
  }
  
  // Cuando se haya logrado la conexión, el programa avanzará, por lo tanto, puede informarse lo siguiente
  Serial.println();
  Serial.println("WiFi conectado");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());

  // Si se logro la conexión, encender led
  
  if (WiFi.status () > 0){
  digitalWrite (statusLedPin, LOW);
  }
  
  delay (1000); // Esta espera es solo una formalidad antes de iniciar la comunicación con el broker

  // Se inicia Conexión con el broker MQTT
  client.setServer(server, 1883); // Conectarse a la IP del broker en el puerto indicado
  client.setCallback(callback); // Activar función de CallBack, permite recibir mensajes MQTT y ejecutar funciones a partir de ellos
  delay(1500);  // Esta espera es preventiva, espera a la conexión para no perder información 
  timeLast = millis (); // Inicia el control de tiempo
   
  
} // fin del void setup



void loop() {

//Verificar siempre que haya conexión al broker
  if (!client.connected()){
    reconnect();  // En caso de que no haya conexión, ejecutar la función de reconexión, definida despues del void setup ()
     }// fin del if (!client.connected())
  
  client.loop(); // Esta función es muy importante, ejecuta de manera no bloqueante las funciones necesarias para la comunicación con el broker
  
    timeNow = millis(); // Control de tiempo para esperas no bloqueantes// read the analog / millivolts value for pin 2:

// Se obtiene la lectura análogica del sensor MQ135
      int analogValue = analogRead(34);
      int analogVolts = analogReadMilliVolts(34);
    
      
   // Secuencia que se asegura de que la conexión con el sensor MQ135 exista
    if (isnan(analogValue) || isnan(analogVolts)) {
      Serial.println(F("Falla al leer el sensor!"));
      return;
    }
    
  // Se imprimen los valores de las lecturas del sensor MQ135 
  Serial.printf("ADC analog value = %d\n",analogValue);        // Se imprime el valor análogico
  Serial.printf("ADC millivolts value = %d\n",analogVolts);    // Se imprime el valor del voltaje añalogicos
  delay(1000);

// Se inician las lecturas del sensor DHT11
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);


  // Checa si hay falla en el sensor DHT11 al momento de realizar las lecturas 
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Falló lectura en el sensor dht11!"));
    return;
  }


  Serial.print(F("Humedad: "));  // Impresión de valor de Humedad
  Serial.print(h);
  Serial.print(F(" %  Temperatura: ")); //Impresión de valor de Humedad
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.println(" ");
  
  delay(5000);  // Retardo entre lecturas del sensor DHT11, se manda un mensaje por MQTT cada cinco segundos
  
  
  if (timeNow - timeLast > wait) { // 
    timeLast = timeNow; // Actualización de seguimiento de tiempo

    

   
    // Se crea el archivo json con los id de los sensores y su lecturas  que se enviarán al broker local mediante el prótocolo mqtt
    
    String json = "{\"id\":\"MQ135_DHT11\",\"ValorAnalogico\":"+String(analogValue)+",\"VoltajeAnalogico\":"+String(analogVolts)+",\"Temperatura\":"+String(t)+",\"Humedad\":"+String(h)+"}";
    
    Serial.println(json); // Se imprime en monitor solo para poder visualizar que el string esta correctamente creado
    
    int str_len = json.length() + 1;//Se calcula la longitud del string
    
    char char_array[str_len];//Se crea un arreglo de caracteres de dicha longitud
    
    json.toCharArray(char_array, str_len);//Se convierte el string a char array    
    
    client.publish("Habeetat/sensores/dht11mqtt", char_array);  // Se publica el archivo json en el tópico Habeetat/sensores/dht11mqtt
     
  }// fin del if (timeNow - timeLast > wait)


  delay(5000);  // Retardo entre lecturas para evitar lecturas erroneas de los sensores
  
  
  
} // fin del void loop


// Funciones de usuario

// Esta función permite tomar acciones en caso de que se reciba un mensaje correspondiente a un tema al cual se hará una suscripción, se crea esta función con el fin de
// conectar un actuador

void callback(char* topic, byte* message, unsigned int length) {

  // Indicar por serial que llegó un mensaje
  Serial.print("Llegó un mensaje en el tema: ");  // Muestra un mensaje si llego una publicación al tema Habeetat/sensores/camara/entrada
  Serial.print(topic);

  // Concatenar los mensajes recibidos para conformarlos como una varialbe String
  String messageTemp; // Se declara la variable en la cual se generará el mensaje completo  
  for (int i = 0; i < length; i++) {  // Se imprime y concatena el mensaje
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }

  // Se comprueba que el mensaje se haya concatenado correctamente
  Serial.println();
  Serial.print ("Mensaje concatenado en una sola variable: ");
  Serial.println (messageTemp);

  // En esta parte se pueden agregar las funciones que se requieran para actuar según se necesite al recibir un mensaje MQTT

  // Ejemplo, en caso de recibir el mensaje true - false, se enciende o se apaga el led
  
  if (String(topic) == "Habeetat/sensores/camara/entrada") {  // En caso de recibirse mensaje en el tema Habeetat/sensores/camara/entrada
    if(messageTemp == "true"){
      Serial.println("Led encendido");
      digitalWrite(flashLedPin, HIGH);
    }// fin del if (String(topic) == "Habeetat/sensores/camara/entrada")
    else if(messageTemp == "false"){
      Serial.println("Led apagado");
      digitalWrite(flashLedPin, LOW);
    }// fin del else if(messageTemp == "false")
  }// fin del if (String(topic) == "Habeetat/sensores/camara/entrada")
}// fin del void callback

// Función para reconectarse
void reconnect() {
  // Bucle hasta lograr conexión
  while (!client.connected()) { // Pregunta si hay conexión
    
    Serial.print("Tratando de conectarse...");
    
    // Intentar reconexión
    
    if (client.connect("ESP32Client")) { //Pregunta por el resultado del intento de conexión, si hay más de un dispositivo conectado al mismo tópico tiene que tener disntinto nombre
                                          // Poner nombre distinto a ESP32Client
      
      Serial.println("Conectado");
      client.subscribe("Habeetat/sensores/camara/entrada"); // Esta función realiza la suscripción al tema
    
    }// fin del  if (client.connect("ESP32Client"))
    
    else {  //en caso de que la conexión no se logre
      Serial.print("Conexion fallida, Error rc=");
      Serial.print(client.state()); // Muestra el codigo de error
      Serial.println(" Volviendo a intentar en 5 segundos");
      // Espera de 5 segundos bloqueante
      delay(5000);
      Serial.println (client.connected ()); // Muestra estatus de conexión
    }// fin del else
  }// fin del bucle while (!client.connected())
}// fin de void reconnect(
