// 10/20/2016

#include <Adafruit_NeoPixel.h>  
#include <ESP8266WiFi.h>
#include <Streaming.h>
#include "weMosPins.h"
//#include "effects.h"

// OTA lib
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>

const char* g_ssid = "Remote1";
const char* g_password = "1234567890";

//Config(
IPAddress g_ip(192,168,0,100); 
IPAddress g_dns(192,168,0,13);
IPAddress g_gateway(192,168,0,1); 
IPAddress g_subnet(255,255,255,0);

String g_restString = "";
volatile boolean g_clear_flag = false;   // clear escape flag

// Create an instance of the g_server
// specify the port to listen on as an argument

WiFiServer g_server(80);
WiFiClient g_client;

// Adafruit_NeoPixel g_strip[5] ; 

void setup() {
    
  setup_effects();  
  g_restString.reserve(256); // program wifi buffer  
  Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  pinMode(weMosBUILTIN_LED, OUTPUT);
  digitalWrite(weMosBUILTIN_LED, LOW);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(g_ssid);
  
  WiFi.config(g_ip,g_gateway,g_subnet); 
  WiFi.begin(g_ssid, g_password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  
  digitalWrite(weMosBUILTIN_LED, LOW);delay(1000);digitalWrite(weMosBUILTIN_LED, HIGH);delay(1000);
  digitalWrite(weMosBUILTIN_LED, LOW);delay(1000);digitalWrite(weMosBUILTIN_LED, HIGH);delay(1000);
     
  // Start the g_server
  g_server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

  // Start the "Over The Air" Update
  setup_OTA();
}

void loop() { 
// OTA server.
  yield();
  ArduinoOTA.handle();  
// Producer
  wiFiFetch();    // adds cmds to buffer g_restString
  breakDetect();  // if break detected clear all 
// Consumer
  parseBuffer(g_restString); // removes cmds from buffer and executes

/*
  // Prepare the response
  g_client.flush();
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (val)?"high":"low";
  s += "</html>\n";

  // Send the response to the client
  g_client.print(s);
  delay(1);
  Serial.println("Client disonnected");
  */
  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

