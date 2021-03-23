#include "BluetoothSerial.h"
#include <Arduino.h>
int pin_DAC=25;
int pin_ADC=34;
int LED=2;


//DECLARO VARIABLES GLOBALS
//Declaro els pins amb un nom per a que s'entengui bé el codi;


void led(){
  for(int i=0;i<10;i++){
    digitalWrite(LED,HIGH);
    Serial.println("ON");
    delay(500);
    digitalWrite(LED,LOW);
    Serial.println("OFF");
    delay(500);
  }
}

void adc_dac(){

  int valor=0;
 
      for (int cont= 0; cont < 256; cont++){
        dacWrite(pin_DAC, cont);
        delay(50);
        valor = analogRead(pin_ADC);
        valor = map(valor, 0, 4096, 0, 255); // EL MAXIM QUE OBTINDRE AL LLEGIR SERA 4096 (2^12), AIXÍ QUE ARA EL 4096 SERÀ 255;
        Serial.println("VALOR:");
        Serial.println(valor);
        delay(100);
      }
  
}

void coments(){
    Serial.println("1. LED");
    Serial.println("2. ADC");
}

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {

  Serial.begin(9600);

  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  pinMode(LED,OUTPUT);

}
void loop() {

if(SerialBT.available()) {
  char a = SerialBT.read();
  
    if(a=='1'){
      
      led();
      coments();
      a=SerialBT.read();
    }
    else if(a=='2'){
      
      adc_dac();
      coments();
      a=SerialBT.read();

    }
}

/**
if (Serial.available()) {
SerialBT.write(Serial.read());
}
if (SerialBT.available()) {
Serial.write(SerialBT.read());
}
**/
delay(20);

}
