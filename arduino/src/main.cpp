#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>



const char* ssid = "Telefon MI";
const char* password = "Barcelona1";

const char* serverAddress = "http://192.168.43.212:5000/hooks";
unsigned long previousTime = 0; // Zmienna przechowująca poprzednią wartość millis()
const unsigned long interval = 60 * 5*1000; // Czas w milisekundach (5 minut)
const char* board_id = "1234";

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
    pinMode(33,OUTPUT);
    pinMode(25,INPUT_PULLUP);
}
void loop() {
    
    
    int przyciskState = digitalRead(25);
   
    if(przyciskState==LOW)
    {
        
    // Odczytaj stan GPIO
        const char* miejsce="warsztat 027";
        DynamicJsonDocument jsonDoc(200);
        jsonDoc["place"] =miejsce ;
        jsonDoc["state"]="hanged";
        jsonDoc["board_id"] = board_id;
        String payload;
        serializeJson(jsonDoc,payload);
        // Wyślij żądanie POST na serwer Flask
        HTTPClient http;
        http.begin(serverAddress);
        http.addHeader("Content-Type", "application/json");
        int httpResponseCode = http.sendRequest("POST", payload);
        Serial.print(httpResponseCode);
        if(httpResponseCode > 0)
        {
            digitalWrite(33,HIGH);
            Serial.printf("HTTP Response code: %d\n",httpResponseCode );
            String response = http.getString();
            Serial.print(miejsce);
            DynamicJsonDocument jsonDoc(200);
            deserializeJson(jsonDoc, response);
            String success = jsonDoc["success"].as<String>();
            Serial.println(response);
            delay(1000);
            
        }
        else
        { 
            
            while (1) {
                digitalWrite(33, HIGH);
                delay(500);
                digitalWrite(33, LOW);
                delay(500);
                przyciskState = digitalRead(25);

                if( przyciskState==HIGH)
                {
                    break;
                }
                
            }
            
            Serial.printf("HTTP Request failed %s\n", http.errorToString(httpResponseCode).c_str()); 
        }
        http.end();
    }
    else
    {
        digitalWrite(33,LOW);
    }
   
    
    if (millis() - previousTime >= interval) 
    {
        previousTime = millis();

        // Wysyłaj informacje co 5 minut niezależnie od stanu przycisku
        const char* miejsce = "warsztat 027";
        DynamicJsonDocument jsonDoc(200);
        jsonDoc["place"] = miejsce;
        jsonDoc["state"] = "check";
        jsonDoc["board_id"] = board_id;
        String payload;
        serializeJson(jsonDoc, payload);
        // Wyślij żądanie POST na serwer Flask
        HTTPClient http;
        http.begin(serverAddress);
        http.addHeader("Content-Type", "application/json");
        int httpResponseCode = http.sendRequest("POST", payload);
        delay(1000);
    if (httpResponseCode > 0) {
        Serial.printf("HTTP Response code: %d", httpResponseCode);
        String response = http.getString();
        DynamicJsonDocument jsonDoc(200);
        deserializeJson(jsonDoc, response);
        String success = jsonDoc["success"].as<String>();
        Serial.println(response);
    }
    else {
        Serial.printf("HTTP Request failed %s", http.errorToString(httpResponseCode).c_str());
    }
    http.end();
    }
    
}

