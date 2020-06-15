int resis =A0;
int Value;
float Voltage;

void setup() {
    pinMode(resis,INPUT);
    Serial.begin(9600);
}

void loop() {
    Value = analogRead(resis);
    Voltage = (5./1023.)*Value;
    Serial.println (Voltage);
    Serial.println (Value);
    delay(250);
}