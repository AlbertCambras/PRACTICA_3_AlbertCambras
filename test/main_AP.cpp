#include <WiFi.h>        // Include the Wi-Fi library
#include <WebServer.h>

// Configuración de la WiFi generada
const char *ssid = "esp-32";
const char *password = "albertcambras";
WebServer server(80); // Object of WebServer(HTTP port, 80 is defult)

void handle_root(void);

void setup() {
  Serial.begin(9600);
  delay(10);
  
  WiFi.mode(WIFI_AP);
  while(!WiFi.softAP(ssid, password))
  {
   Serial.println(".");
    delay(100);
  }

  server.on("/", handle_root);
  server.begin();
  Serial.println("HTTP server started");

  Serial.print("Iniciado AP ");
  Serial.println(ssid);
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());
  
}
 
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

void handle_root(){
server.send(200, "text/html", HTML);
}
