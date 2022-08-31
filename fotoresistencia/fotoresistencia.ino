#define Photoresistor A0 

void setup() {
  Serial.begin(9600);  
}

void loop() {
  int analog_value = analogRead(Photoresistor);
  Serial.println(analog_value);
  delay(100);
}
