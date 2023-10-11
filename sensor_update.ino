

#include "DHT.h" 
#define DHTPIN D1
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 

#include "UbidotsMicroESP8266.h"
#define TOKEN  "BBFF-6OEvwzWC562JTqE12o9rvEu2jgnib1"  // Put here your Ubidots TOKEN
#define WIFISSID "Vaibhav"
#define PASSWORD "11111111"
int vs = A0;
int vs1 = D0;
int percentValue = 0;
Ubidots client(TOKEN);
unsigned long lastMillis = 0;

void setup(){
    Serial.begin(115200);
    dht.begin();
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);
    pinMode(vs ,INPUT);
    pinMode(vs1 ,INPUT);
    Wire.begin(2,0);
    lcd.init();
    lcd.backlight();
    lcd.home();
}
void loop(){

    if (millis() - lastMillis > 10000) {  ///every 10S

      float humedad = dht.readHumidity();
      float temperatura = dht.readTemperature();
      float data      = analogRead(vs);
      float data1      = digitalRead(vs1);
      percentValue = map(data, 1023, 200, 0, 100);
            lastMillis = millis();
            client.add("humrel", humedad);
            client.add("temperature", temperatura);
            client.add("soil", percentValue);
             client.add("LDR", data1);
            client.sendAll(true);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("H:"); lcd.print(humedad); lcd.print("% S:"); lcd.print(percentValue); lcd.print("%");
            lcd.setCursor(0,1);
            lcd.print("T:"); lcd.print(temperatura); lcd.print("C L:"); lcd.print(data1); lcd.print("%");   
            
            delay(500);
            }

 
   
}
