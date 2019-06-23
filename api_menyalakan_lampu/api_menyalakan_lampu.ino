#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

ESP8266WiFiMulti WiFiMulti;

// set variabel pin untuk lampu
int pompa = D7;
int lamp =D6;
int OutKipas=D8;
int OutFood=D5;

void setup()
{
    Serial.begin(115200);

    // set Wifi SSID dan passwordnya
    WiFiMulti.addAP("Crocodic Frontend", "crocodichebat");

    // set pin mode ke output
    pinMode(pompa, OUTPUT);
    pinMode(lamp, OUTPUT);
    pinMode(OutKipas,OUTPUT);
    pinMode(OutFood,OUTPUT);
}

void loop()
{
    // tunggu koneksi Wifi
    if((WiFiMulti.run() == WL_CONNECTED))
    {
      // inialisaisi http pompa
        HTTPClient http;
        
        // get data status pompa
        http.begin("http://neptune.crocodic.net/ta/public/api/get_status_iot?id=1");

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
      

                // cek value json
                if(doc["status"]=="active" && doc["id"]==1){
                    // set ke LOW untuk menyalakan
                    digitalWrite(pompa, HIGH);
                } else {
                    // set ke HIGH untuk mematikan
                    digitalWrite(pompa, LOW);
                }
            }

        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        // tutup koneksi HTTP
        http.end();

        //controll lampu

        // inialisaisi http lampu
        HTTPClient control_lamp;

        //get data statius LED

        control_lamp.begin("http://neptune.crocodic.net/ta/public/api/get_status_iot?id=2");
          // mulai koneksi dan ambil HTTP Header
        int httpLamp = control_lamp.GET();
        // httpCode akan bernilai negatif bila error
        if(httpLamp > 0)
        {
            // cetak httpCode ke Serial
            Serial.printf("[HTTP] GET... code: %d\n", httpLamp);

            // bila nilai dari server diterima
            if(httpLamp == HTTP_CODE_OK)
            {
      
                // cetak string json dari server
                String json1 = control_lamp.getString();
                Serial.println(json1);

                //parse value json

               DynamicJsonDocument doc1(1024);
               DeserializationError error1 = deserializeJson(doc1, json1);
               
              // Parameters
              int id1 = doc1["id"]; 
              Serial.println(id1);
      

                // cek value json
                if(doc1["status"]=="active" && doc1["id"]==2){
                    // set ke LOW untuk menyalakan
                    digitalWrite(lamp, HIGH);
                } else {
                    // set ke HIGH untuk mematikan
                    digitalWrite(lamp, LOW);
                }
            }
          
        }else{
          Serial.printf("[HTTP] GET... failed, error: %s\n", control_lamp.errorToString(httpLamp).c_str());
        }
        control_lamp.end();

        // inialisaisi kipas
        HTTPClient kipas;

        //get data statius kipas

        kipas.begin("http://neptune.crocodic.net/ta/public/api/get_status_iot?id=3");
        
          // mulai koneksi dan ambil HTTP Header
        int httpKipas = kipas.GET();
        // httpCode akan bernilai negatif bila error
        if(httpKipas > 0)
        {
            // cetak httpCode ke Serial
            Serial.printf("[HTTP] GET... code: %d\n", httpKipas);

            // bila nilai dari server diterima
            if(httpKipas == HTTP_CODE_OK)
            {
      
                // cetak string json dari server
                String json2 = kipas.getString();
                Serial.println(json2);

                //parse value json

               DynamicJsonDocument doc2(1024);
               DeserializationError error2 = deserializeJson(doc2, json2);
               
              // Parameters
              int id2 = doc2["id"]; 
              Serial.println(id2);
      

                // cek value json
                if(doc2["status"]=="active" && doc2["id"]==3){
                    // set ke LOW untuk menyalakan
                    digitalWrite(OutKipas, HIGH);
                } else {
                    // set ke HIGH untuk mematikan
                    digitalWrite(OutKipas, LOW);
                }
            }
          
        }else{
          Serial.printf("[HTTP] GET... failed, error: %s\n", kipas.errorToString(httpKipas).c_str());
        }
        kipas.end();

         // inialisaisi http pompa
        HTTPClient food;
        
        // get data status pompa
        food.begin("http://neptune.crocodic.net/ta/public/api/get_status_iot?id=4");

        // mulai koneksi dan ambil HTTP Header
        int httpFood = food.GET();
        // httpCode akan bernilai negatif bila error
        if(httpFood > 0)
        {
            // cetak httpCode ke Serial
            Serial.printf("[HTTP] GET... code: %d\n", httpFood );

            // bila nilai dari server diterima
            if(httpFood  == HTTP_CODE_OK)
            {
      
                // cetak string json dari server
                String json3 = food.getString();
                Serial.println(json3);

                //parse value json

               DynamicJsonDocument doc3(1024);
               DeserializationError error3 = deserializeJson(doc3, json3);
               
              // Parameters
              int id3 = doc3["id"]; 
              Serial.println(id3);
      

                // cek value json
                if(doc3["status"]=="active" && doc3["id"]==4){
                    // set ke LOW untuk menyalakan
                    digitalWrite(OutFood, HIGH);
                } else {
                    // set ke HIGH untuk mematikan
                    digitalWrite(OutFood, LOW);
                }
            }

        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", food.errorToString(httpFood).c_str());
        }
        // tutup koneksi HTTP
        food.end();
    }

    delay(5000);
}
