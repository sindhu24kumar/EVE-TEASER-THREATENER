#include <ESP8266WiFi.h>

#include <WiFiClient.h>

#include <ESP8266WebServer.h>

#define SSID1 "police"
#define PASSWORD "police12345"
String latitude,longitude;
ESP8266WebServer server(80);

void handleRoot() {

server.send(200, "text/html", "<h1>You are connected</h1>");
}
void handlelatlong(){
  
latitude=server.arg(0);
longitude=server.arg(1);
Serial.println("[ALERT] made on gps coordinates !");
Serial.print("Latitude:");
Serial.println(latitude);
Serial.print("Longitude:");
Serial.println(longitude);
server.send(200, "text/html", "<h1>OK</h1>");
  }

void setup() {

delay(1000);

Serial.begin(9600);

Serial.println("WELCOME TO POLICE EMERGENCY NETWORK");

Serial.print("Configuring access point...");

Serial.println();


WiFi.softAP(SSID1, PASSWORD);

IPAddress myIP = WiFi.softAPIP();

Serial.print("AP IP address: ");

Serial.println(myIP);

server.on("/", handleRoot);

server.on("/senddata", handlelatlong);

server.begin();

Serial.println("HTTP server started");

}

void loop() {

server.handleClient();

}
