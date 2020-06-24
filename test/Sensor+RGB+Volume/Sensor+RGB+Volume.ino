const int trig = 12;
const int echo = 13;
const int LED1 = 3;
const int LED2 = 5;
const int LED3 = 6;

int duration = 0;
int distance = 0;

int resis =A0;
int Value;
int Voltage;
void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  Serial.begin(9600);
  pinMode(resis,INPUT);
}
void loop() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig, LOW);

  Voltage = analogRead(resis);
  Value = (64./1023.)*Voltage;

  duration = pulseIn(echo, HIGH);
  distance = (duration*0.034) / 2;

  Serial.println(distance);
  if (distance <= 10) {
    analogWrite(LED1, 0);
    analogWrite(LED2, Value);
    analogWrite(LED3, 0);
  }
  else if (distance <= 20 && distance > 10) {
    analogWrite(LED1, Value);
    analogWrite(LED2, Value/2);
    analogWrite(LED3, 0);
  } 
  else if (distance <= 60 && distance > 20) {
    analogWrite(LED1, Value);
    analogWrite(LED2, 0);
    analogWrite(LED3, 0);
  } 
}