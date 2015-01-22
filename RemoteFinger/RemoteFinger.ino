/*
  Web Server
 
 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)
 
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 
 */

#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h> 
#include "DHT.h"
 
#define DHTPIN 7 // what pin we're connected to
#define DHTTYPE DHT11 // DHT 11

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 
IPAddress ip(192,168,1, 177);
boolean estado = false;
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
DHT dht(DHTPIN, DHTTYPE); //temp humidity
 
int pos = 0;    // variable to store the servo position 
int step = 45;

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(3001);
String request = "";
String getPath = "GET /";
String postPath = "POST /";
  
void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  //servo
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 

  myservo.write(0);

  //temp
  Serial.println("DHTxx test!");
 
  dht.begin();
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;
        //Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {

          Serial.println();
          Serial.println("Received request");
          Serial.println(request);

          if(request.indexOf("GET / HTTP/1.1") >= 0) {
            Serial.println("It's default path");
            // send a standard http response header
            sendDefaultPage(client);

          } else if(request.indexOf(getPath) >= 0 && request.indexOf("HTTP/1.1") >= 0) {
            int startIndex = request.indexOf(getPath) + getPath.length();
            int endIndex = request.indexOf("HTTP/1.1") - 1;
            Serial.print("detected path:");
            String detectedPath = request.substring(startIndex, endIndex);
            Serial.print(detectedPath);
            Serial.println(":");

            String clave = "yourpassword";
            if(clave.equals(detectedPath)) {
              press(40);
              estado = !estado;
            }

            sendDefaultPage(client);

          } else if(request.indexOf(postPath) >= 0 && request.indexOf("HTTP/1.1") >= 0) {
            int startIndex = request.indexOf(postPath) + postPath.length();
            int endIndex = request.indexOf("HTTP/1.1") - 1;
            Serial.print("detected path:");
            Serial.print(request.substring(startIndex, endIndex));
            Serial.println(":");
            sendDefaultPage(client);

          } else {
            Serial.println("Unable to handle request");
          }

          request = "";

          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void sendDefaultPage(EthernetClient client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.println("<head>");
  client.println("<script>");
  client.println("press = function(pass){");
  client.println("  var req = new XMLHttpRequest();");
  client.println("  req.open(\"GET\", pass, true);");
  client.println("  req.send(null);");
  client.println("  history.go(0);");
  client.println("}");
  client.println("</script>");
  client.println("</head>");

  client.println("<body>");
  client.print("Temperatura: ");
  // Read temperature as Celsius
  float t = dht.readTemperature();
  
  if(isnan(t)) {
    client.println("Error");
  } else {
    client.println(t);
  }
  client.println("<BR/>");
  client.print("Humedad: ");
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  if(isnan(h)) {
    client.println("Error");
  } else {
    client.println(h);
  }
  client.println("<BR/>");
  client.print("Estado: ");
  client.println(estado?"Encendido":"Apagado");
  client.println("<BR/>");
  client.println("<BR/>");
  client.println("Password: <input type=\"password\" id=\"password\"/>");
  client.print("<button type=\"button\" id=\"button\" onclick=\"javascript:press(password.value);\">");
  client.print(estado?"Apagar":"Encender");
  client.println("</button>");
  client.println("</body>");
  client.println("</html>");
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

