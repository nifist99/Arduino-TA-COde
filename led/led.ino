void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 pinMode(D7, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
const char* status = "active";
   if(status=="active"){
                    // set ke LOW untuk menyalakan
                    digitalWrite(D7, LOW);
                } else {
                    // set ke HIGH untuk mematikan
                    digitalWrite(D7, HIGH);
                }

}
