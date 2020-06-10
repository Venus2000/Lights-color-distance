 const int echo = 13;
 const int trig = 12;
 
 int duration = 0;
 int distance = 0;

 void setup() {
     
     pinMode(trig, OUTPUT);
     pinMode(echo, INPUT);
     Serial.begin(9600);
 }
 void loop() {
     
     digitalWrite(trig, HIGH);
     delayMicroseconds(1000);
     digitalWrite(trig, LOW);

     duration = pulseIn(echo, HIGH); //ดึงสัญญาณมา
     distance = (duration*0.034) / 2; //เวลาคูณด้วยความเร็ว
     Serial.println(distance);
 }