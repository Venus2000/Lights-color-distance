int resis =A0;
int Value;
int Voltage;

void setup() {
    pinMode(resis,INPUT);
    Serial.begin(9600);
}

void loop() {
    Value = analogRead(resis);
    Voltage = (32./1023.)*Value;
    Serial.println (Voltage);
    //Serial.println (Value);
    delay(250);
}