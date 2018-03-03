#include "SoftwareSerial.h"
//white d6
SoftwareSerial serial_connection(D5, D6);
void setup() {
pinMode(D8,INPUT);  
Serial.begin(9600);
serial_connection.begin(9600);
Serial.println("Boot");
}

void loop() {
  
if(digitalRead(D8) == 1){
  Serial.println("ON"); 
  serial_connection.write(2);
  }else{
    serial_connection.write(3);
    }
delay(1000);
}

