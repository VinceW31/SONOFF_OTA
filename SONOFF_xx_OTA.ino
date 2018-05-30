//This is a blank example file

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h> //This line is for OTA support, do not delete or change

MDNSResponder mdns;
// Replace with your network credentials
const char* ssid = ".........."; //insert your SSID
const char* password = ".........."; //insert your Password

ESP8266WebServer server(80);
String webPage = "";

//GPIO & LED pins
const int Led = 13;
const int Relay = 12;


void setup(){
//These lines are for OTA support, do not delete or change*****************************
  ArduinoOTA.onError([](ota_error_t error) { ESP.restart(); });
  ArduinoOTA.begin();
//*************************************************************************************

//Insert sketch code from here*********************************************************

//Web Page Design
  webPage += "<h1 style='text-align:center;'>SONOFF 119</h1><h2 style='text-align:center;'>(fw ver 12)</h2><p style='text-align:center;'><a href=\"on\"><button style='font-size:170%;'>ON</button></a>&nbsp;&nbsp<a href=\"off\"><button style='font-size:170%;'>OFF</button></a></p>";  

// Initialise
  pinMode(Led, OUTPUT);
  pinMode(Relay, OUTPUT);

  digitalWrite(Led, HIGH);
  digitalWrite(Relay, LOW);
  
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
  server.on("/", [](){
    if(digitalRead(Relay)==HIGH) {
      server.send(200, "text/html", webPage);
    } else {
      server.send(200, "text/html", webPage);
    }
  });
  server.on("/on", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(Led, LOW);
    digitalWrite(Relay, HIGH);
    delay(1000);
  });
  server.on("/off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(Led, HIGH);
    digitalWrite(Relay, LOW);
    delay(1000); 
  });
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(){
  ArduinoOTA.handle(); //This line is for OTA support, do not delete or change position

//Insert sketch code from here*********************************************************


  
  server.handleClient(); //This line is for OTA support, do not delete or change*****************************
} 
