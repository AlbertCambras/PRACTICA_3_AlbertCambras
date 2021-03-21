
#include <WiFi.h>
#include <WebServer.h>
// SSID & Password
const char* ssid = "MOVISTAR_AB50"; // Enter your SSID here
const char* password = "935888966"; //Enter your Password here
WebServer server(80); // Object of WebServer(HTTP port, 80 is defult)

// Handle root url (/)
void handle_root(void);


void setup() {

Serial.begin(9600);
Serial.println("Try Connecting to ");
Serial.println(ssid);

// Connect to your wi-fi modem
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
server.on("/", handle_root);
server.begin();
Serial.println("HTTP server started");
delay(100);
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