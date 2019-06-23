#include <ESP8266WiFi.h>

const char* ssid = “node”; //ganti nama wifi
const char* pass = “12345678”;//ganti password

WiFiClient client;

void setup() 
{
Serial.begin(9600);
delay(10);

Serial.print(” Menghubungkan ke : “);
Serial.println(ssid);

WiFi.begin(ssid, pass); 
while (WiFi.status() != WL_CONNECTED) 
{
delay(500);
Serial.print(“….”);
}
Serial.print(“\n”);
Serial.print(“IP address : “);
Serial.println(“”);
Serial.print(“Terhubung dengan : “);
Serial.println(ssid); 
}

void loop() { }
