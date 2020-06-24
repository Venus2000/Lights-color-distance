#include "LiquidCrystal_I2C.h" // includes the LiquidCrystal Library
LiquidCrystal_I2C
    lcd(0x27, 16,
        2); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
const int trigPin = 12;
const int echoPin = 13;
long duration;
int distanceCm = 0;
int detect = 5;
int buzzer = 8;
int val = 0;
void setup() {
  lcd.init();
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  Serial.println(distanceCm);
  /*if (distanceCm <= 5) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }*/
  IR();
  lcd.setCursor(0, 0); // Sets the location at which subsequent text written to
                       // the LCD will be displayed
  lcd.print("Distance"); // Prints string "Distance" on the LCD
  lcd.setCursor(0, 1);
  lcd.print(distanceCm); // Prints the distance value from the sensor
  lcd.setCursor(4, 1);
  lcd.print(" cm");
  delay(10);
}
void IR() {
  if (distanceCm <= 5) {
    val = analogRead(detect);
    Serial.println(val);
    if (val > 500) {
      digitalWrite(buzzer, 0);
      digitalWrite(2, 1);
    } else {
      digitalWrite(buzzer, 1);
      digitalWrite(2, 0);
    }
  }
}