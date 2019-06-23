#include <Wire.h> 

const int senseInput = A0; //Set to A0 as Analog Read
int senseRawValue; //Some variable
float senseTurbidity; //Some floating variable
float kekeruhan;
 
void setup(){
  Serial.begin(9600); //Set as serial communication baud rate 9600
  Serial.println(" 14CORE | TURBIDITY SENSING ANALOG TEST CODE ");
  Serial.println("Initializing.................................");
  delay(4000);
}
void loop(){
senseRawValue = analogRead(senseInput); //Read input raw value fromt the sensor
senseTurbidity = senseRawValue * (3.0 / 1024.0); //Convert analog data from 0 -1024 to voltage 0 - 5v;
Serial.println("TURBIDITY VALUE > "); //Print the output data to the serial
Serial.println(senseTurbidity);
Serial.println("kekeruhan");
kekeruhan=100.00-(senseTurbidity/1.50)*100.00;
Serial.println(kekeruhan);
Serial.println("nilai ADC");
Serial.println(senseRawValue);
delay(5000);

 
}
