#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h> //This line is for OTA support, do not delete or change

//  FW Ver 26, Platform IO upload

MDNSResponder mdns;

const char* ssid = "xxxx";
const char* password= "yyyy";

ESP8266WebServer server(80);
String webPage = "";
String webPageON = "";
String webPageOFF = "";

//GPIO & LED pins
const int Led = 13;
const int Relay = 12;
const int Ext_Sw = 14; //14 for Sonoff Basic, 04 for Sonoff Mini

int previousButtonState;
int trigger;
int debounceDelay = 250; 

void setup(){
//These lines are for OTA support, do not delete or change*****************************
  ArduinoOTA.onError([](ota_error_t error) { ESP.restart(); });
  ArduinoOTA.begin();
//*************************************************************************************

//Insert sketch code from here*********************************************************

//Web Page Design
  webPage += "<h1 style='text-align:center;'>SONOFF 134 - Xmas Lights Controller</h1><h2 style='text-align:center;'>(fw ver 26)</h2><p style='text-align:center;'><a href=\"on\"><button style='font-size:170%;'>ON</button></a>&nbsp;&nbsp<a href=\"off\"><button style='font-size:170%;'>OFF</button></a></p><p style='text-align:center;'><button style='font-size:170%;'>STATUS</button></p>";  
  webPageON += "<h1 style='text-align:center;'>SONOFF 134 - Xmas Lights Controller</h1><h2 style='text-align:center;'>(fw ver 26)</h2><p style='text-align:center;'><a href=\"on\"><button style='font-size:170%;'>ON</button></a>&nbsp;&nbsp<a href=\"off\"><button style='font-size:170%;'>OFF</button></a></p><p style='text-align:center;'><button style='font-size:170%;background-color:lime;'>STATUS</button></a></p>";  
  webPageOFF += "<h1 style='text-align:center;'>SONOFF 134 - Xmas Lights Controller</h1><h2 style='text-align:center;'>(fw ver 26)</h2><p style='text-align:center;'><a href=\"on\"><button style='font-size:170%;'>ON</button></a>&nbsp;&nbsp<a href=\"off\"><button style='font-size:170%;'>OFF</button></a></p><p style='text-align:center;'><button style='font-size:170%;background-color:red;'>STATUS</button></a></p>";  

// Initialise
  pinMode(Led, OUTPUT);
  pinMode(Relay, OUTPUT);
  pinMode(Ext_Sw, INPUT_PULLUP);
  digitalWrite(Led, HIGH);
  digitalWrite(Relay, LOW);
  
  previousButtonState = digitalRead(Ext_Sw); //Initialise to make sure relay is OFF on reboot
  
  Serial.begin(115200); 
  delay(5000);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  server.on("/", [](){ //status check
    if(digitalRead(Relay)==HIGH) {
      server.send(200, "text/html", webPageON);
    } else {
      server.send(200, "text/html", webPageOFF);
    }
  });
  server.on("/on", [](){ //switch ON
    server.send(200, "text/html", webPageON);
    digitalWrite(Led, LOW);
    digitalWrite(Relay, HIGH);
    delay(1000);
  });
  server.on("/off", [](){ //switch OFF
    server.send(200, "text/html", webPageOFF);
    digitalWrite(Led, HIGH);
    digitalWrite(Relay, LOW);
    delay(1000); 
  });
  server.on("/cycle", [](){ //Cyle relay ON/ OFF/ ON (to get around ESP32 intermittent power ON issue)
    server.send(200, "text/html", webPageON);
    digitalWrite(Led, LOW);
    digitalWrite(Relay, HIGH);
    delay(1000); 
    digitalWrite(Relay, LOW);
    delay(1000); 
    digitalWrite(Relay, HIGH);
    delay(1000); 
  });
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(){
  ArduinoOTA.handle(); //This line is for OTA support, do not delete or change position

//Insert sketch code from here*********************************************************

// Check status of Ext Switch on GPIO14
  int currentButtonState = digitalRead(Ext_Sw);
  int RelayState = digitalRead(Relay);
  
  if (currentButtonState != previousButtonState) { //if the Ext Switch has changed state
    delay(debounceDelay); // wait a bit
    if (currentButtonState != previousButtonState) { //if the Ext Switch is still in a changed state
      if (RelayState == 1) { // if RELAY is CLOSED 
        digitalWrite(Relay, LOW); // OPEN the RELAY
        digitalWrite(Led, HIGH);  // & turn LED OFF
      } else { //otherwise, if RELAY is OPEN 
        digitalWrite(Relay, HIGH); // CLOSE the RELAY
        digitalWrite(Led, LOW); // & turn LED ON
      }
      previousButtonState = currentButtonState; //reset the previous state of the Ext Switch    
    }
  }
  
  server.handleClient();
} 
