void setup() {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}
void loop() {
  delay(1000);
  analogWrite(3, 32);
  analogWrite(5, 0);
  analogWrite(6, 0);
  delay(1000);

  analogWrite(3, 32);
  analogWrite(5, 32);
  analogWrite(6, 32);
  delay(1000);
  
  analogWrite(3, 0);
  analogWrite(5, 32);
  analogWrite(6, 0);
}