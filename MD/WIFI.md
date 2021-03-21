
## **PRACTICA 2.1 : WIFI**
Para hacer este proyecto hay que insertar dos librerías las cuales servirán para conectarse al Wifi y crear un servidor con la placa.
Estas librerías ya han sido creadas por otros usuarios por lo que no pararé a explicar como funcionan estas y como se comunican con la ESP32.
Solamente decir que se usan unas funciones de estas para establecer la conexión Wifi, ver el estado de esta conexión y ver la IP de la placa.

Una vez ejecutado el código y subido a la placa, podemos ver principalmente dos cosas:  
    1) Establecimiento de conexión  
    2) Conexión establecida, IP, servidor inicializado.

### **Establecimiento de conexión**

Se realiza gracias a unas funciones de la librería <Wifi.h>, estas son:

``` cs
const char* ssid = "MOVISTAR_AB50"; // Enter your SSID here
const char* password = "935888966"; //Enter your Password 

WebServer server(80); // Object of WebServer(HTTP port, 80 is default)

// Handle root url (/)
void handle_root(void);

void setup(){
WiFi.begin(ssid, password);

// Check wi-fi is connected to wi-fi network
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.print(".");
}

Serial.println("");
Serial.println("WiFi connected successfully");
Serial.print("Got IP: ");
Serial.println(WiFi.localIP()); //Show ESP32 IP on serial
}
```
Primero intentamos conectarnos al Wifi mediante el nombre y contraseña anteriormente especificados en dos punteros char llamadas ssid y password.
Establecemos el puerto al que se conectará la ESP32 del router.

Vemos que se usa el Wifi.status() para informar al usuario de forma gráfica, en este caso con '.' si se ha podido conectar o está habiendo algún problema.
Una vez establecida informa al usuario e imprime la IP de la ESP32 de este.
Esta IP la necesitamos porque se ha creado un servidor local.  
En resumen... Ahora nuestra placa está conectada un Wifi y se ha creado un servidor que podremos acceder mediante la IP de esta. Si queremos acceder a este servidor es necesario estar conectado al mismo Wifi, ya que es un servidor local.





### **Creación del servidor**

Se realiza gracias a unas funciones de la librería <webServer.h>

```cs
server.on("/", handle_root);
server.begin();
Serial.println("HTTP server started");
delay(100);

void loop() {
server.handleClient();
}

// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>PAGINA ESP32 DE ALBERT CAMBRAS </h1>\
<h2> Esto es un código de HTML enviado con la placa ESP32. </h2>\
</body>\
</html>";
// Handle root url (/)
void handle_root() {
server.send(200, "text/html", HTML);
}
```
webServer nos srive para recibir y enviar información, procesarla y guardarla. También la podemos usar para enviar la información a una web.
Para comunicarse se usa el protocolo *HTTP*.
Cuando enviamos alguna cosa al servidor, nos devuelve un codigo:  
- 200 Si la conexión se ha establecido correctamente.
- 404 Si no se ha podido estanlecer.

En este caso primero de todo se inicializa el servidor.
Dentro la función loop() se llama a handle_Client el cual he supuesto que establece la conexión cliente.

Fuera de esta podemos crear nuestro código html para la página web y con una función enviarla al servidor.
El código en html creado lo ponemos dentro de una variable de tipo String que le llamamos HTML. 
  

## **WIFI ACCES-POINT (AP)**

En este caso tenemos todo lo contrario a lo anterior, la placa ya no se conectará al wifi y creará un servidor local si no que se comportará como punto de acceso, es decir será como un router al que nos podremos conectar. 
Esto nos puede servir para cuando tenemos un proyecto y queremos comunicarnos con el móvil o otros nodos pero no tenemos internet para conectarnos. No tendría sentido tener que depender de Wifi de un sitio para poder hacer funcionar nuestro proyecto.

La programación para este ejemplo es bastante parecida a la anterior.

### **Establecimiento de conexión**

``` cs
const char* ssid = "esp-32"; // Enter your SSID here
const char* password = "albertcambras"; //Enter your Password here
WebServer server(80); // Object of WebServer(HTTP port, 80 is default)

// Handle root url (/)
void handle_root(void);

void setup(){
WiFi.begin(ssid, password);

void setup() {
  Serial.begin(9600);
  delay(10);
  
  WiFi.mode(WIFI_AP);
  while(!WiFi.softAP(ssid, password))
  {
   Serial.println(".");
   delay(100);
  }
}
```
Anteriormente teníamos que ingresar en las variables *ssid* y *password* el nombre de nuestro router y contraseña. En cambio ahora aquí pondremos como queremos llamar a nuestro nuevo router y la contraseña que tendremos que aplicar.

La función Wifi.mode nos permite seleccionar como queremos que actúe la placa, modo AP o como el anterior.
Por defecto viene la anterior por eso no la habíamos especificado.

Dentro del setup() inicializamos el puerto serie y enseñamos de forma gráfica al usuario si se ha podido establecer como punto de acceso.
Por defecto se asigna una IP y una máscara de red, yo en mi caso no la he modificado pero podríamos usar las siguientes funciones fuera del setup para cambiarlas

```cs
Ejemplo direcciones IP, máscara de red.

IPAddress local_ip(192,168,5,1);
IPAddress gateway(192,168,5,1);
IPAddress subnet(255,255,255,0);
```
Ahora si subieramos el código a la placa no debería haber ningún problema. Podríamos mirar las redes wifi disponibles y veríamos el nombre que le hemos asignado.
Si intentamos conectarnos veríamos que no tiene internet. Eso es porque nos hemos conectado al router ESP-32 pero este no tiene acceso a internet y entonces el dispositivo tampoco. Igualmente gracias a esto tenemos disponible una red Wifi entre los que se conecten a esta (esta librería tiene por defecto 4 usuarios) y podríamos acceder a un servidor web por ejemplo con el que podríamos enviar y recibir información.  
Para hacer este servidor web he usado los mismos parámetros anteriormente explicados.
Solo se podrá acceder a esta web si se está conectado al wifi de la ESP32. 
Para acceder a este wifi el nombre y contraseña son:  

**ssid=esp-32**  
**password=albertcambras**

    
 ## **Conclusiones** 
  
  No he tenido demasiados problemas a la hora de realizar esta práctica. lo único que al principio me fallaba era el entrar a la web ya que no estaba conectado a la misma red Wifi que la placa y por lo tanto no me cargaba nada al ingresar la IP en el navegador.
  Una vez he resuelto el problema todo funcionaba como tenía que ser.
  El código HTML no he usado el md de la anterior práctica ya que era muy largo y ya se entendía la idea, he estado probando algunos comandos html y me funcionaban igual de bien.

## DIAGRAMA DE FLUJO

![DIAGRAMA DE FLUJO](DIAGRAMA_FLUJO.jpg)





