/*
Author: Alejandro Zalazar
IR Remote controlled 3 wheeled vehicle, with 2 motors
*/ 

#include <IRremote.h>
#include <Servo.h>
#include <DCMotor.h>

// Declare Servo
Servo MiServo;
// Motors
DCMotor motor0(M0_EN, M0_D0, M0_D1);
DCMotor motor1(M1_EN, M1_D0, M1_D1); //right wheel on m1
// IR receiver
IRrecv irReceiver(A0);

int LastValue, Received, RecChar;

void setup()
{
  // Init Serial Port
   Serial.begin(9600);
   LastValue = Received = 0;
   // Attach Servo to S5
   MiServo.attach(A5);
   // Set Buzzer/Speaker to Output
   pinMode(SPEAKER, OUTPUT);
}

void loop()
{
  Received = irReceiver.getIRRemoteCode();
  if (Received != LastValue) {
    // Something different received from IR, show it
    if (Received) {
      Serial.print("IR data received: ");
      Serial.println(Received);
      if(Received == 2) {//forward
         motor0.setSpeed(70);
         motor1.setSpeed(70); 
      } else if(Received == 5) {//backwards
         motor0.setSpeed(-70);
         motor1.setSpeed(-70); 
      } else if(Received == 3) {// right
         motor0.setSpeed(70);
         motor1.setSpeed(-70); 
      } else if(Received == 1) {//left 
         motor0.setSpeed(-70);
         motor1.setSpeed(70); 
      } else {
         motor0.setSpeed(0); //stop
         motor1.setSpeed(0); 
      }
    }
    LastValue = Received;
  }
  
}
