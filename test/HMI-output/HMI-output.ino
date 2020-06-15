#test2

void setup(void) {
 
Serial.begin(9600);
 
progmemPrintln(PSTR("TFT LCD test"));
 
#ifdef USE_ADAFRUIT_SHIELD_PINOUT
progmemPrintln(PSTR("Using Adafruit 2.8\" TFT Arduino Shield Pinout"));
#else
progmemPrintln(PSTR("Using Adafruit 2.8\" TFT Breakout Board Pinout"));
#endif
 
tft.reset();
 
tft.begin(0x9341); // SDFP5408
 
tft.setRotation(0); //เลื่อนหรือสไลด์
 
 
progmemPrintln(PSTR("Benchmark Time (microseconds)"));
 
progmemPrint(PSTR("Screen "));
Serial.println(testFillScreen());
delay(500);
 
progmemPrint(PSTR("Text "));
Serial.println(testText());
delay(3000);
 
 
progmemPrintln(PSTR("Done!"));
}
 
void loop(void) {
testText();
delay(5000);
}
 
unsigned long testFillScreen() {
unsigned long start = micros();
tft.fillScreen(BLACK);
tft.fillScreen(RED);
tft.fillScreen(GREEN);
tft.fillScreen(BLUE);
tft.fillScreen(BLACK);
return micros() - start;
}
 
unsigned long testText() {
tft.fillScreen(BLACK);
unsigned long start = micros();
tft.setCursor(0, 0);
tft.setTextColor(WHITE); tft.setTextSize(1);
tft.println("Hello test");
tft.setTextColor(YELLOW); tft.setTextSize(2);
tft.println(1234.56);
tft.setTextColor(RED); tft.setTextSize(3);
tft.println("arduino test");
tft.println();
tft.setTextColor(GREEN);
tft.setTextSize(5);
tft.println("Arduino");
tft.setTextSize(2);
tft.println("br venus");
tft.setTextSize(1);
tft.println("");
tft.println("Venus");
 
}
 
void progmemPrint(const char *str) {
char c;
while(c = pgm_read_byte(str++)) Serial.print(c);
}
 
void progmemPrintln(const char *str) {
progmemPrint(str);
Serial.println();
}
