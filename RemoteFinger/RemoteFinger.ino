// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 

String inString = "";
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
int step = 45;
 
void setup() 
{ 
  Serial.begin(9600);

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 

  myservo.write(0);

} 
 
 
void loop() 
{ 

  readAndMove();
} 

void readAndMove() {
  //apretar
  //press(38);
}

void press(int deg) {
    for(pos = 0; pos < deg; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = deg; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
}



