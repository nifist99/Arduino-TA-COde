#include <Wire.h> 

const int SENSOR =A0;

static float kekeruhan;
static float tegangan;

void setup()
{
  Serial.begin(9600);
  pinMode(SENSOR,INPUT);
}

void loop()
{
  int voltage=analogRead(SENSOR);
  tegangan=voltage*(3.3/1024);
  Serial.println(tegangan);
  delay(3000);
}
