#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#define LED 2
#define LED2 4

const char* ssid = "Telefon MI";
const char* password = "Barcelona1";

const char* serverAddress = "http://192.168.43.212:5000/gpio_state";
<<<<<<< Updated upstream

=======
bool secondledstate=false;
bool automaticLedState = false;
>>>>>>> Stashed changes
void setup(){
    Serial.begin(115200);
    delay(1000);

    WiFi.mode(WIFI_STA); //Optional
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }
    pinMode(LED,OUTPUT);
    pinMode(LED2,OUTPUT);
}

void loop() {
     if (!automaticLedState) {
        digitalWrite(LED, HIGH);
    }
    // Odczytaj stan GPIO
   int gpioState = 10 ;
    DynamicJsonDocument jsonDoc(200);
    jsonDoc["gpioState"] = gpioState;
    String payload;
    serializeJson(jsonDoc,payload);
    // Wyślij żądanie POST na serwer Flask
    HTTPClient http;
    http.begin(serverAddress);
    http.addHeader("Content-Type", "application/json");
<<<<<<< Updated upstream
     int httpResponseCode = http.sendRequest("POst", payload);
=======
     int httpResponseCode = http.sendRequest("POST", payload);
    if  (!secondledstate) 
    { digitalWrite(LED2, HIGH); }
>>>>>>> Stashed changes
    if(httpResponseCode > 0)
    {
        Serial.printf("HTTP Response code: %d\n",httpResponseCode );
        String response = http.getString();
        DynamicJsonDocument jsonDoc(200);
        deserializeJson(jsonDoc, response);
        String success = jsonDoc["success"].as<String>();
         if (success == "true") { secondledstate = true; digitalWrite(LED2, HIGH); }
        Serial.println(response);
        
        digitalWrite(LED,HIGH);
        delay(1000);
        digitalWrite(LED,LOW);
    }
    else
    {
        Serial.printf("HTTP Request failed %s\n", http.errorToString(httpResponseCode).c_str());
        digitalWrite(LED2, LOW);
    }
     if (automaticLedState) {
        digitalWrite(LED, LOW);
        automaticLedState = false;
    }
  
    http.end();
    
    delay(1000);
   
}