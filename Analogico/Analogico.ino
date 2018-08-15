void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
}

void loop() {
  int sensorValue = analogRead(A0);
  Serial.print(sensorValue);
  Serial.print(",");
  Serial.flush();
  delay(1000);

}
