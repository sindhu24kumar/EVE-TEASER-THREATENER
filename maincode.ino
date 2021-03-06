#include <ESP8266WiFi.h>
#include "TinyGPS++.h"
#include "SoftwareSerial.h"
#include <ESP8266HTTPClient.h>
#define SSID1 "police"
#define PASSWORD "police12345"
#define WIFI_SSID "emergency"
int i = 10;
int counter = 1;
#define PIN_BUZZER D1
String server="192.168.4.1";
//d6 blu d5purpple
SoftwareSerial serial_connection(D5, D6);
SoftwareSerial serial_connection_2(D3, D2);
TinyGPSPlus gps;
WiFiClient client;


void  wifi_connection(char *ssid, char* passwd)
{
  WiFi.begin(ssid, passwd);
//  Serial.println(ssid);
//   Serial.println(passwd);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WIFI Connection Failed! Retrying...");
    delay(50);
    wifi_connection(ssid,passwd);
    
  }
  Serial.println("WIFI connected successfully..");
}

void setup() {

  Serial.begin(9600);
  Serial.println("Booting..");

  pinMode(PIN_BUZZER, OUTPUT);
  serial_connection.begin(9600);
   serial_connection_2.begin(9600);
  Serial.println("GPS Start");
 
  while (1) {
    look_for_wifi_ssid();
    if(counter>1){
       send_gps();
      }
      if(serial_connection_2.available()){
        Serial.println(serial_connection_2.read());
        if(serial_connection_2.read()==2){
          buzzer_on();
          }else{
            buzzer_off();
            }
        }
      
  }
}
void send_lat_long_police(double lati,double longi){
  wifi_connection(SSID1,PASSWORD);
//  String dummy_url=url;
//  dummy_url+=String(lati);
//  dummy_url+="&longitude=";
//  dummy_url+=String(longi);

   if (client.connect(server, 80)) {
    Serial.println("connected to server");
 //uncomment these lines incase gps works   
//    // Make a HTTP request: for gps data get success
//    String req1="GET /senddata?lat=";
//    req1+=String(lati);
//    String req2="&lon=";
//    req2+=String(longi);
//    req2+=" HTTP/1.1";
//    req1+=req2;
Serial.println("\nStarting connection to server...");
//comment lines if gps -- start
    String req1="GET /senddata?lat=";
    req1+="12.234324";
    String req2="&lon=";
    req2+="24.2343242";
    req2+=" HTTP/1.1";
    req1+=req2;
 // - end   
    Serial.println(req1);
    client.println(req1);
    client.println("Host: 192.168.4.1");
    client.println("Connection: close");
    client.println();
    while (client.available()) {
    char c = client.read();
    Serial.write(c);
    }
  }else{
    Serial.println("Connection to police  servers failed");
    }
  
  }
void buzzer_on(){
  Serial.println("GPS data send - button action");
  

  
      while (serial_connection.available()) {
    gps.encode(serial_connection.read());
  }
  if( gps.location.isUpdated()) {
    Serial.println("Latitude:");
    Serial.println(gps.location.lat(), 6);
    Serial.println("Longitude:");
    Serial.println(gps.location.lng(), 6);

  
  }
  Serial.println("SENDING__lat:19.022323 , lon:23.232424 ");
  send_lat_long_police(19.022323,23.232424);
  Serial.println("Buzzer on");
  digitalWrite(PIN_BUZZER, HIGH);
  
  }
  void buzzer_off(){
    Serial.println("Buzzer off");
  digitalWrite(PIN_BUZZER, LOW);
  }
void send_gps() {

  Serial.println("GPS data send");
  

  
      while (serial_connection.available()) {
    gps.encode(serial_connection.read());
  }
  if( gps.location.isUpdated()) {
    Serial.println("Latitude:");
    Serial.println(gps.location.lat(), 6);
    Serial.println("Longitude:");
    Serial.println(gps.location.lng(), 6);
  //send_lat_long_police(gps.location.lat(),gps.location.lng());
  //send_lat_long_police(19.022323,23.232424);
  
  }
    Serial.println("lat:19.022323 , lon:23.232424 ");
  send_lat_long_police(19.022323,23.232424);
}
void look_for_wifi_ssid() {

  Serial.println("*SCAN NETWORKS*");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    Serial.println("Couldn't get a wifi connection");
    while (i > 0) {
      look_for_wifi_ssid();
      i = i - 1;
    }
  }
  i = 10;
  for (int scan = 0; scan < numSsid; scan++) {
    if (WiFi.SSID(scan) == WIFI_SSID ) {
      counter++;

      Serial.println("GOT WIFI");
      Serial.println(counter);
      digitalWrite(PIN_BUZZER, HIGH);
      delay(500);
      digitalWrite(PIN_BUZZER, LOW);
      if (counter > 1) {
       
        return;
      }

    }

  }
}
void loop() {

}
