//  void setup_OTA(void); 

//const char* ssid = "..........";
//const char* password = "..........";

void setup_OTA() {
  /* switch OFF led */
  pinMode(weMosBUILTIN_LED, OUTPUT);
  digitalWrite(weMosBUILTIN_LED, HIGH);
  
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
    digitalWrite(weMosBUILTIN_LED, HIGH);
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
    digitalWrite(weMosBUILTIN_LED, LOW);
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });

  Serial << "ESP8266-Tree1" << endl;
  WiFi.hostname("ESP8266-Tree1");
  MDNS.addService("http", "tcp", 80);
  ArduinoOTA.setHostname("ESP8266-Tree1");

  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
