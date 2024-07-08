#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <string>
#include <bitmap.h>
#include <WiFiManager.h>
#define BUTTON1_PIN 25
#define BUTTON2_PIN 26
#define BUTTON_WEB_PIN 14


TFT_eSPI tft = TFT_eSPI();

const char* ssid_self = "HACZYK";
const char* password_self = "haczykowanie";

const char* SERVER_ADDRESS = "https://hangwatch.knr.edu.pl/hooks"; 

const char* BOARD_ID = "box";
const char* MIEJSCE = "boks b2.01";
const char* HASLO = "tajne hasło";

void IRAM_ATTR buttonAction_Falling();
void IRAM_ATTR buttonAction_Rising();
void IRAM_ATTR buttonAction_WebServer();
int get_status();
int send_status_request(bool buttonState);
void loading();
void setupMode();

class Button{
    public:
        bool isPressed;
        uint16_t Pin;
        const char* states[2]={"Student","Piwo"};
};

Button button1;
Button button2;
Button buttonWeb;


void setup()
{
    Serial.begin(115200);
    delay(1000);
    button1.Pin = BUTTON1_PIN;
    button2.Pin = BUTTON2_PIN; 
    buttonWeb.Pin = BUTTON_WEB_PIN;
    buttonWeb.isPressed = false; //tryb setupu musi byc wylaczony przy bootowaniu
    button1.isPressed = false;

    tft.init(); //wlaczenie wysweitalcza
    tft.textsize=2;
    tft.fillScreen(TFT_BLACK);
    
    pinMode(button1.Pin,INPUT_PULLUP);
    attachInterrupt(button1.Pin,buttonAction_Falling,FALLING);
    attachInterrupt(button2.Pin,buttonAction_Rising,RISING);
    attachInterrupt(buttonWeb.Pin,buttonAction_WebServer,FALLING); 
    
    setupMode();
}
void loop() 
{   
    int httpResponseCode;
    if(buttonWeb.isPressed == true){
        setupMode();
    }
    
    if(button1.isPressed == true){
        int status027 = get_status();
        tft.fillRect(0,20,128,40,TFT_BLACK);
        tft.drawBitmap(39,60,logo,50,53,TFT_BLACK,TFT_CYAN);
        httpResponseCode = send_status_request(button1.isPressed);
        while(httpResponseCode != 200){
        httpResponseCode = send_status_request(button1.isPressed);
        
        }
        while(button1.isPressed==true){
        tft.drawBitmap(39,60,logo,50,53,TFT_BLACK,TFT_WHITE);
        
        tft.setCursor(10,10);
        tft.textsize = 1; 
        tft.setTextColor(TFT_WHITE,TFT_BLACK);
        tft.print("STATUS STUDENTA");
        tft.setCursor(10,20);
        if(status027== 0 ){
            tft.print("027 zamkniete");
        }
        else if(status027 == 1){
            tft.print("027 otwarte");
        }
        else if(status027 == 2){
            tft.print("027 offline");
        }
        tft.textsize = 2;
        tft.setCursor(10,40);
        tft.setTextColor(TFT_RED,TFT_BLACK);
        tft.print(button1.states[1]);
        }
        
    }
    else{
       tft.fillRect(0,20,128,40,TFT_BLACK);
        tft.drawBitmap(39,60,logo,50,53,TFT_BLACK,TFT_CYAN);
        httpResponseCode = send_status_request(button1.isPressed);
        int status027 = get_status();
        while(httpResponseCode != 200){
        tft.fillRect(0,10,128,40,TFT_BLACK);
        tft.setCursor(100,10);
        

        httpResponseCode = send_status_request(button1.isPressed);
        
        }
        while(button1.isPressed==false){
        
        tft.drawBitmap(39,60,logo,50,53,TFT_BLACK,TFT_WHITE);
        tft.setCursor(10,10);
        tft.textsize = 1; 
        tft.setTextColor(TFT_WHITE,TFT_BLACK);
        tft.print("STATUS STUDENTA");
        tft.setCursor(10,20);
        if(status027 == 0 ){
            tft.print("027 zamkniete");
        }
        else if(status027 == 1){
            tft.print("027 otwarte");
        }
        else if(status027 == 2){
            tft.print("027 offline");
        }
        tft.textsize = 2;
        tft.setCursor(10,40);
        tft.setTextColor(TFT_GREEN);
        tft.print(button1.states[0]);
        }
       
    }
   
}


void IRAM_ATTR buttonAction_Falling(){
 button1.isPressed = false; 
}
void IRAM_ATTR buttonAction_Rising(){
 button1.isPressed = true;
}
void IRAM_ATTR buttonAction_WebServer(){
buttonWeb.isPressed = !buttonWeb.isPressed;
}
int send_status_request(bool buttonState)
{
    
    DynamicJsonDocument jsonDoc(200);
    jsonDoc["place"] =  MIEJSCE;
    if(buttonState==false)
    {
        jsonDoc["state_"] = "hanged";
    }
    else
    {
        jsonDoc["state"]="empty";
    }
    jsonDoc["password"]=HASLO;
    jsonDoc["board_id"] = BOARD_ID;
    String payload;
    serializeJson(jsonDoc, payload);
    // Wyślij żądanie POST na serwer Flask
    HTTPClient http;
    http.begin(SERVER_ADDRESS);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.sendRequest("POST", payload);
    http.end();
    loading();
    return httpResponseCode;
}
void loading(){
    int whiteRect_Y = 150;
    int whiteRect_X = 0;
    int whiteRect_Height = 4;
    int whiteRect_Width = 128;
    int rectSpace = 1;
    int barWidth = 1;
    int barHeight = 2;
    tft.setTextColor(TFT_WHITE);
    tft.drawRect(whiteRect_X,whiteRect_Y,whiteRect_Width,whiteRect_Height,TFT_WHITE);
    for(int i = whiteRect_X + rectSpace; i<=whiteRect_Width-rectSpace;i++){
        tft.fillRect(i,whiteRect_Y + rectSpace,barWidth,barHeight,TFT_GREEN);
        delay(6);
    }
    tft.fillRect(whiteRect_X,whiteRect_Y,whiteRect_Width, whiteRect_Height,TFT_BLACK);
    
}
void setupMode(){
    tft.fillRect(0,10,158,90,TFT_BLACK);
    tft.drawBitmap(39,60,logo,50,53,TFT_BLACK,TFT_LIGHTGREY);
    tft.setCursor(10,10);
    tft.textsize = 1; 
    tft.setTextColor(TFT_WHITE,TFT_BLACK);
    tft.print("TRYB SETUPU");
    tft.setTextColor(TFT_CYAN,TFT_BLACK);
    tft.setCursor(10,30);
    tft.print(ssid_self);
    tft.setCursor(10,40);
    tft.print(password_self);

    WiFiManager wm;
    wm.setConfigPortalTimeout(300);
    if(!wm.startConfigPortal(ssid_self,password_self)){
        tft.fillRect(0,10,128,40,TFT_BLACK);
        tft.setCursor(10,10);
        tft.print("timeout");
        delay(3000);
        
        
    }
    tft.fillRect(0,10,128,40,TFT_BLACK);
    tft.textsize = 2;
    buttonWeb.isPressed = false;
}
int get_status(){
    HTTPClient http;
    http.begin(SERVER_ADDRESS);
    DynamicJsonDocument jsonDoc(200);
    int responseCode = http.GET();
    String payload = "{}" ;
    jsonDoc["board_id"] = 1234;
    serializeJson(jsonDoc, payload);
    if(responseCode > 0){
        payload = http.getString();
    }
    http.end();
    if(payload = "empty"){
        return 0;
    }
    else if(payload = "hanged"){
        return 1;
    }
    else{
        return 2;
    }
    }





