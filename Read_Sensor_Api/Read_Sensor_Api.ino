#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);
ESP8266WiFiMulti WiFiMulti;

static char celcius_str[15];

float Celcius=0;
float Fahrenheit=0;


void setup()
{
    Serial.begin(115200);
    sensors.begin();
    // set Wifi SSID dan passwordnya
    WiFiMulti.addAP("Crocodic Frontend", "crocodichebat");

}

void loop()
{

    // tunggu koneksi Wifi
    if((WiFiMulti.run() == WL_CONNECTED))
    {
          sensors.requestTemperatures(); 
          Celcius=sensors.getTempCByIndex(0);

          Serial.println(Celcius);
  
        HTTPClient http;

        HTTPClient updateSuhu;
        
        // get data status suhu
        http.begin("http://neptune.crocodic.net/ta/public/api/read_sensor?id=1");

        // mulai koneksi dan ambil HTTP Header
        int httpCode = http.GET();
        // httpCode akan bernilai negatif bila error
        if(httpCode > 0)
        {
            // cetak httpCode ke Serial
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // bila nilai dari server diterima
            if(httpCode == HTTP_CODE_OK)
            {

               // cetak string json dari server
                String json = http.getString();
                Serial.println(json);

                //parse value json

               DynamicJsonDocument doc(1024);
               DeserializationError error = deserializeJson(doc, json);
               
              // Parameters
              int id = doc["id"]; 
              Serial.println(id);

         // cast nilai float celsius ke type char dahulu agar dapat digabung
        // parameter kedua panjang karakter, 
        // parameter ketiga adalah panjang karakter setelah koma 
         dtostrf(Celcius, 5, 2, celcius_str);


         String url="http://neptune.crocodic.net/ta/public/api/update_sensor?id=1&value=";

         String urls=url+celcius_str;

//         Serial.println(urls);

              if(doc["id"]==1 && doc["status"]=="active"){
                 if(doc["value"] != Celcius){
                  updateSuhu.begin(urls);
                      int httpSuhu = updateSuhu.GET();
        // httpCode akan bernilai negatif bila error
        if(httpSuhu > 0)
        {
          if(httpSuhu == HTTP_CODE_OK)
            {

                String json1 = updateSuhu.getString();
                Serial.println(json1);

          Serial.println("success update");
            }
        }
                 }
              }  
              
            } 

         }else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        // tutup koneksi HTTP
        http.end();
      }
      delay(10000);
    }
