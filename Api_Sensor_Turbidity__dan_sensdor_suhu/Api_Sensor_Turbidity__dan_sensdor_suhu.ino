#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <OneWire.h>
#include <Wire.h> 
#include <DallasTemperature.h>


//Sensor suhu
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
ESP8266WiFiMulti WiFiMulti;
static char celcius_str[15];
float Celcius=0;
float Fahrenheit=0;

//sensor turbidity
const int senseInputTurbidity = A0; //Set to A0 as Analog Read
int senseRawValueTurbidity=0; //Some variable
float senseTurbidity=0; //Some floating variable
float kekeruhan=0;
static char turbidity_str[15];


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
        updateSuhu.end();
        http.end();

        //Ini adalah Sensor turbidity atau kekeruhan
        senseRawValueTurbidity = analogRead(senseInputTurbidity); //Read input raw value fromt the sensor
        senseTurbidity = senseRawValueTurbidity * (3.0 / 1024.0); //Convert analog data from 0 -1024 to voltage 0 - 5v;
        Serial.println("TURBIDITY VALUE > "); //Print the output data to the serial
        Serial.println(senseTurbidity);
        Serial.println("kekeruhan");

        //angka 1.60 adalah kalibrasi awal dengan air jernih
        kekeruhan=100.00-(senseTurbidity/1.60)*100.00;
        Serial.println(kekeruhan);
        Serial.println("nilai ADC");
        Serial.println(senseRawValueTurbidity);

        HTTPClient httpGetTurbidity;
        HTTPClient httpUpdateTurbidity;

             // get data status suhu
        httpGetTurbidity.begin("http://neptune.crocodic.net/ta/public/api/read_sensor?id=2");

        // mulai koneksi dan ambil HTTP Header
        int httpValueGet = httpGetTurbidity.GET();
        // httpCode akan bernilai negatif bila error
        if(httpValueGet > 0)
        {
                 // cetak httpCode ke Serial
            Serial.printf("[HTTP] GET... code: %d\n", httpValueGet);

            // bila nilai dari server diterima
            if(httpValueGet == HTTP_CODE_OK)
            {

               // cetak string json dari server
                String json1 = httpGetTurbidity.getString();
                Serial.println(json1);

                //parse value json

               DynamicJsonDocument doc1(1024);
               DeserializationError error1 = deserializeJson(doc1, json1);
               
              // Parameters
              int id1 = doc1["id"]; 
              Serial.println(id1);

         // cast nilai float celsius ke type char dahulu agar dapat digabung
        // parameter kedua panjang karakter, 
        // parameter ketiga adalah panjang karakter setelah koma 
         dtostrf(senseTurbidity, 5, 3,turbidity_str);
         String url_turbidity="http://neptune.crocodic.net/ta/public/api/update_sensor?id=2&value=";

     
       

         String urls_turbidity=url_turbidity+turbidity_str;
         Serial.println(urls_turbidity);

           if(doc1["id"]==2 && doc1["status"]=="active"){
              if(doc1["value"] != senseTurbidity){
                 httpUpdateTurbidity.begin(urls_turbidity);
                 int httpTurbidityCekUpdate = httpUpdateTurbidity.GET();
        // httpCode akan bernilai negatif bila error
        if(httpTurbidityCekUpdate > 0)
        {
          if(httpTurbidityCekUpdate == HTTP_CODE_OK)
            {

                String json_turbidity_update = httpUpdateTurbidity.getString();
                Serial.println(json_turbidity_update);

                Serial.println("success update");
            }
        }
                 }
              }  
              
            }//kurung tutup httpsuccess
          
        }

          httpGetTurbidity.end();
         httpUpdateTurbidity.end();

        
      }
      delay(10000);
    }
