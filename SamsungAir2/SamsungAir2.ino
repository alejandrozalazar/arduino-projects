#include "IRremote.h"
#include <Arduino.h>

IRsend irsend;
String readString;

int khz = 38; //NB Change this default value as neccessary to the correct modulation frequency
void setup() {
  // Serial.begin(9600);
  Serial.begin(115200);

  Serial.println("serial on"); // so I can keep track
}


unsigned on[] ={500, 550, 500, 1550, 450, 600, 550, 500, 450, 550, 550, 550, 500, 550, 500, 550, 450, 600, 500, 1500, 500, 550, 550, 500, 500, 1550, 450, 600, 500, 550, 450, 1550, 550, 1500, 500, 1550, 500, 1500, 500, 1550, 500, 550, 500, 550, 450, 600, 550, 550, 450, 600, 450, 550, 500, 550, 500, 550, 500, 550, 500, 500, 500, 550, 500, 600, 500, 500, 500, 550, 500, 550, 450, 600, 550, 500, 450, 600, 450, 550, 500, 550, 500, 550, 500, 550, 550, 500, 500, 550, 450, 600, 450, 550, 500, 600, 450, 550, 500, 550, 500};
unsigned my30[] ={500, 550, 550, 1500, 450, 550, 500, 600, 500, 550, 450, 550, 500, 550, 500, 550, 450, 650, 500, 1500, 500, 550, 500, 550, 500, 1550, 450, 600, 450, 600, 450, 1550, 500, 1550, 500, 1550, 500, 1550, 450, 1550, 500, 550, 500, 550, 450, 600, 550, 550, 500, 550, 450, 550, 500, 550, 500, 550, 550, 500, 500, 550, 450, 600, 500, 550, 450, 550, 550, 500, 500, 550, 450, 600, 450, 550, 550, 550, 450, 550, 500, 550, 500, 550, 500, 550, 500, 550, 550, 500, 500, 550, 450, 550, 500, 550, 500, 550, 500, 550, 500};
unsigned my29[] ={500, 550, 500, 1550, 500, 550, 550, 500, 500, 550, 450, 600, 500, 550, 450, 600, 450, 550, 550, 1500, 500, 550, 500, 550, 500, 1550, 500, 550, 450, 600, 450, 1600, 450, 1550, 550, 1500, 450, 1600, 450, 1550, 500, 600, 500, 500, 500, 550, 500, 550, 450, 600, 500, 550, 500, 550, 450, 600, 450, 600, 500, 550, 450, 550, 500, 550, 500, 550, 500, 600, 450, 550, 500, 550, 500, 550, 500, 550, 450, 550, 500, 550, 500, 600, 500, 550, 450, 600, 450, 550, 550, 550, 450, 550, 500, 550, 500, 500, 500, 600, 500};
unsigned my28[] ={500, 550, 500, 1550, 450, 550, 500, 600, 500, 500, 500, 550, 500, 550, 450, 650, 450, 600, 450, 1550, 500, 550, 500, 550, 500, 1550, 450, 600, 450, 600, 450, 1550, 550, 1500, 500, 1550, 450, 1550, 500, 1550, 500, 550, 500, 550, 450, 600, 500, 550, 450, 600, 500, 550, 500, 550, 450, 600, 550, 450, 500, 600, 450, 550, 500, 550, 500, 550, 500, 550, 500, 500, 500, 550, 500, 600, 450, 550, 500, 550, 500, 550, 450, 600, 500, 550, 450, 600, 450, 550, 500, 550, 500, 550, 500, 550, 500, 550, 500, 550, 550};
unsigned my27[] ={500, 550, 500, 1550, 500, 550, 500, 550, 500, 550, 450, 600, 450, 550, 500, 550, 500, 600, 500, 1550, 450, 600, 450, 550, 500, 1550, 500, 550, 450, 600, 500, 1550, 450, 1600, 450, 1550, 500, 1550, 450, 1550, 500, 600, 450, 550, 500, 550, 500, 550, 500, 550, 450, 600, 450, 600, 500, 550, 500, 550, 500, 550, 500, 550, 500, 550, 500, 550, 450, 600, 450, 600, 500, 550, 450, 550, 500, 550, 500, 550, 500, 550, 450, 550, 500, 550, 500, 550, 500, 550, 500, 550, 500, 550, 450, 600, 500, 550, 500, 500, 500};
unsigned my26[] ={500, 550, 500, 1550, 500, 550, 500, 550, 450, 600, 500, 500, 550, 550, 500, 500, 500, 550, 500, 1550, 500, 550, 500, 550, 500, 1550, 450, 600, 500, 550, 450, 1600, 500, 1500, 500, 1550, 500, 1500, 500, 1550, 500, 600, 450, 550, 500, 550, 500, 550, 500, 550, 500, 550, 500, 550, 500, 550, 450, 600, 500, 500, 500, 550, 500, 600, 500, 500, 500, 550, 500, 550, 500, 550, 500, 550, 500, 550, 500, 550, 450, 600, 500, 550, 500, 550, 500, 550, 450, 550, 500, 600, 450, 550, 500, 550, 500, 550, 500, 550, 500};
unsigned my25[] ={500, 550, 500, 1550, 450, 550, 500, 600, 450, 550, 500, 550, 500, 550, 450, 650, 450, 600, 450, 1550, 500, 550, 550, 500, 500, 1550, 450, 600, 500, 550, 450, 1600, 500, 1500, 500, 1550, 450, 1550, 550, 1500, 500, 550, 500, 550, 450, 600, 500, 550, 450, 600, 500, 550, 500, 550, 450, 600, 500, 550, 450, 600, 450, 550, 500, 550, 550, 500, 500, 550, 500, 550, 450, 600, 450, 600, 450, 550, 500, 550, 500, 600, 450, 600, 450, 550, 500, 550, 500, 550, 500, 550, 500, 550, 550, 500, 500, 550, 450, 600, 450};
unsigned my24[] ={500, 550, 500, 1550, 450, 600, 500, 550, 450, 550, 550, 550, 500, 550, 450, 600, 500, 500, 500, 1550, 500, 550, 500, 550, 500, 1550, 450, 550, 500, 550, 500, 1550, 500, 1550, 450, 1550, 500, 1550, 550, 1500, 500, 550, 450, 600, 500, 550, 500, 550, 500, 550, 500, 550, 500, 550, 450, 600, 500, 550, 450, 550, 500, 550, 500, 550, 500, 550, 500, 550, 450, 550, 500, 600, 500, 550, 450, 550, 500, 550, 500, 550, 550, 500, 500, 550, 450, 550, 500, 550, 500, 550, 500, 550, 500, 550, 500, 550, 500, 550, 450};
unsigned my23[] ={500, 550, 500, 1550, 450, 600, 450, 600, 500, 550, 450, 550, 500, 550, 500, 550, 550, 550, 500, 1500, 500, 550, 500, 550, 500, 1550, 450, 600, 550, 450, 500, 1550, 550, 1500, 500, 1550, 500, 1500, 500, 1550, 500, 550, 500, 550, 450, 600, 550, 550, 450, 600, 450, 550, 500, 550, 500, 550, 500, 550, 500, 550, 450, 550, 500, 600, 500, 500, 500, 550, 500, 550, 450, 600, 450, 600, 500, 500, 500, 550, 500, 600, 450, 550, 500, 550, 500, 550, 500, 550, 450, 600, 450, 550, 500, 550, 500, 550, 500, 550, 500};
unsigned my22[] ={500, 550, 500, 1550, 450, 600, 450, 550, 500, 600, 450, 550, 500, 600, 450, 550, 500, 550, 500, 1550, 500, 500, 500, 600, 500, 1500, 500, 600, 500, 500, 500, 1550, 500, 1550, 450, 1600, 450, 1600, 500, 1550, 500, 550, 450, 550, 500, 550, 500, 550, 500, 550, 500, 550, 450, 600, 500, 550, 500, 550, 500, 550, 450, 600, 450, 600, 450, 600, 450, 550, 500, 550, 500, 550, 500, 550, 450, 600, 500, 550, 450, 600, 450, 550, 500, 600, 500, 500, 500, 550, 500, 600, 450, 600, 450, 600, 500, 500, 500, 550, 500};
unsigned my21[] ={500, 550, 500, 1550, 500, 550, 500, 550, 500, 550, 500, 500, 550, 550, 450, 550, 500, 550, 500, 1550, 500, 550, 500, 550, 500, 1550, 500, 550, 500, 550, 450, 1600, 450, 1550, 500, 1550, 500, 1500, 500, 1550, 500, 600, 450, 550, 550, 500, 500, 500, 500, 550, 550, 550, 500, 550, 450, 600, 450, 600, 450, 600, 500, 500, 500, 550, 500, 550, 500, 550, 500, 550, 500, 550, 500, 550, 450, 600, 500, 550, 450, 550, 500, 550, 550, 550, 450, 600, 450, 550, 500, 550, 500, 550, 500, 550, 500, 550, 450, 600, 500};
unsigned my20[] ={500, 550, 550, 1500, 450, 550, 500, 600, 450, 550, 500, 550, 500, 500, 500, 600, 450, 550, 500, 1550, 500, 550, 550, 550, 450, 1600, 450, 550, 500, 550, 500, 1550, 500, 1550, 450, 1550, 500, 1600, 550, 1500, 450, 600, 450, 600, 500, 600, 500, 500, 500, 550, 500, 500, 500, 550, 500, 550, 500, 550, 500, 600, 500, 550, 450, 600, 450, 600, 450, 600, 450, 550, 500, 550, 500, 600, 500, 550, 500, 500, 500, 600, 450, 600, 450, 550, 500, 550, 500, 600, 500, 500, 500, 550, 500, 550, 550, 500, 500, 550, 500};
unsigned my19[] ={500, 550, 500, 1550, 500, 550, 500, 500, 500, 600, 450, 600, 500, 500, 500, 600, 500, 550, 450, 1600, 450, 550, 500, 550, 500, 1550, 500, 550, 500, 550, 450, 1600, 450, 1550, 500, 1550, 500, 1550, 450, 1550, 500, 550, 500, 550, 500, 550, 500, 550, 450, 650, 450, 600, 450, 550, 500, 550, 500, 550, 450, 600, 550, 450, 500, 600, 450, 550, 500, 550, 550, 500, 500, 550, 500, 550, 450, 600, 450, 600, 500, 550, 500, 550, 500, 550, 500, 550, 450, 600, 500, 550, 450, 550, 500, 550, 500, 550, 450, 600, 500};
unsigned my18[] ={550, 550, 450, 1550, 500, 600, 500, 500, 500, 550, 500, 650, 450, 550, 500, 550, 500, 550, 450, 1600, 500, 550, 500, 550, 450, 1600, 450, 650, 450, 550, 500, 1550, 450, 1600, 450, 1550, 550, 1500, 450, 1600, 450, 600, 550, 500, 450, 600, 450, 550, 500, 550, 500, 550, 500, 550, 500, 550, 500, 550, 500, 550, 450, 550, 500, 550, 500, 550, 500, 550, 500, 600, 500, 550, 450, 550, 500, 550, 500, 550, 550, 500, 500, 500, 500, 600, 500, 550, 450, 550, 500, 550, 500, 550, 500, 550, 500, 550, 450, 600, 550};
unsigned my17[] ={500, 600, 550, 1450, 500, 550, 500, 550, 500, 550, 500, 550, 450, 550, 500, 550, 500, 600, 450, 1550, 500, 550, 550, 500, 500, 1550, 500, 550, 500, 550, 450, 1600, 450, 1550, 500, 1550, 500, 1600, 550, 1500, 450, 550, 500, 550, 500, 600, 450, 600, 500, 500, 500, 600, 450, 550, 500, 550, 500, 550, 500, 600, 450, 600, 450, 550, 500, 550, 550, 500, 500, 550, 500, 550, 450, 650, 450, 600, 500, 550, 450, 550, 500, 550, 500, 550, 450, 600, 500, 600, 450, 550, 500, 550, 500, 550, 500, 550, 500, 550, 450};
unsigned my16[] ={550, 500, 500, 1550, 450, 550, 500, 600, 450, 550, 500, 550, 500, 550, 550, 500, 500, 550, 450, 1600, 450, 550, 500, 550, 500, 1550, 500, 1550, 500, 550, 500, 1550, 550, 1500, 450, 1550, 500, 1600, 450, 1550, 500, 600, 450, 550, 500, 550, 500, 550, 500, 550, 500, 550, 500, 550, 550, 550, 500, 550, 500, 550, 500, 550, 550, 550, 500, 550, 500, 550, 500, 550, 500, 600, 500, 550, 500, 550, 500, 600, 500, 550, 550, 500, 550, 500, 550, 500, 550, 550, 500, 550, 500, 600, 500, 550, 500, 550, 500, 550, 500};
unsigned off[] ={500, 600, 500, 1500, 500, 550, 500, 550, 500, 550, 500, 550, 450, 600, 450, 600, 450, 550, 500, 1550, 500, 550, 500, 550, 450, 1600, 500, 1550, 500, 550, 500, 1550, 450, 1550, 500, 1550, 500, 1600, 500, 1550, 450, 550, 500, 600, 450, 550, 500, 550, 500, 550, 500, 550, 500, 550, 550, 500, 500, 600, 500, 550, 500, 600, 500, 550, 450, 600, 500, 550, 500, 600, 450, 550, 550, 550, 500, 550, 500, 550, 550, 500, 550, 550, 500, 550, 500, 550, 550, 550, 550, 500, 500, 550, 550, 550, 500, 550, 500, 550, 500};

void loop() {

  // Serial.print(".");

  while (Serial.available()) {
    delay(3);
    char c = Serial.read();
    readString += c;
  }
  if (readString.length() > 0) {
    readString = readString.substring(0, readString.length() - 1);
    Serial.println(readString);
    if (readString.equals("on")) {
      Serial.println("starting on");
      irsend.sendRaw(on, sizeof(on) / sizeof(int), khz);
      
      Serial.println("ending on");
    } else 
    if (readString.equals("off")) {
      Serial.println("starting off");
      irsend.sendRaw(off, sizeof(off) / sizeof(int), khz);
      
      Serial.println("ending off");
    } else 
    if (readString.equals("23")) {
      Serial.println("starting 23");
      irsend.sendRaw(my23, sizeof(my23) / sizeof(int), khz);
      Serial.print("sizeof ");
      Serial.println(sizeof(my23));
      Serial.println(sizeof(int));
      Serial.println(sizeof(my23) / sizeof(int));
      Serial.println("ending 23");
    } else 
    if (readString.equals("24")) {
      Serial.println("starting 24");
      irsend.sendRaw(my24, sizeof(my24) / sizeof(int), khz);
      Serial.print("sizeof ");
      Serial.println(sizeof(my24));
      Serial.println(sizeof(int));
      Serial.println(sizeof(my24) / sizeof(int));
      
      Serial.println("ending 24");
    } else {
      Serial.print("Command not found:");
      Serial.print(readString);
      Serial.println(":");
    }
    readString = "";
    Serial.println("");
  }
}

