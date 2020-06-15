#include <UTFT.h>
#include <URTouch.h>

//สร้างปุ่มกดอันแรก
UTFT    myGLCD(SSD1289,38,39,40,41); //ปรับพารามิเตอร์
URTouch  myTouch( 6, 5, 4, 3, 2); //กำหนดตัวแปร

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern unsigned int bird01[0x41A];
int x, y;
char currentPage, selectedUnit;

//Ultrasonic Sensor
const int VCC = 13;
const int trigPin = 11;
const int echoPin = 12;
long duration;
int distanceInch, distanceCm;

// RGB 
const int redLed = 3;
const int greenLed = 5;
const int blueLed = 6;
int xR=32;
int xG=32;
int xB=32;

void setup() {
  // ค่าเริ่มต้น
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  // กำหนดพินโหมด
  pinMode(VCC, OUTPUT); // VCC
  pinMode(trigPin, OUTPUT); //  trigPin as an Output
  pinMode(echoPin, INPUT); //  echoPin as an Input
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(VCC, HIGH); // +5V - Pin 13 as VCC
  drawHomeScreen();  // หน้าจอหลัก
  currentPage = '0'; // ปุ่มไปหน้าจอหลัก
  selectedUnit = '0'; // แสดงหน่วยหรือหลัก cm , m 
}
// drawHomeScreen - ฟังก์ชั่นที่กำหนดในจอ
void drawHomeScreen() {
  // Title
  myGLCD.setBackColor(0,0,0); // ตั้งค่าสีพื้นหลังที่จะพิมข้อความลงไป
  myGLCD.setColor(32, 15, 0); // ตั้งค่าข้อความสีตัวหนังสือ
  myGLCD.setFont(BigFont); // ขนาดตัวหนังสือหัวข้อ
  myGLCD.print("Arduino TFT Tutorial", CENTER, 10); // พิมหัวข้อลงไปที่จออันแรก
  myGLCD.setColor(32, 15, 0); // ตั้งค่าสีของตัวหนังสือ
  myGLCD.setFont(SmallFont); // Sets the font to small
  myGLCD.print("by Venus", CENTER, 16); // Prints the string

  // Button - Distance Sensor
  myGLCD.setColor(0, 0, 255); // สีพื้นหลังกล่องข้อความ
  myGLCD.fillRoundRect (35, 90, 285, 130); // Draws filled rounded rectangle
  myGLCD.setColor(32, 15, 0); // สีตัวหนังสือ
  myGLCD.setFont(BigFont); // Sets the font to big
  myGLCD.setBackColor(0, 0, 255); //สีพื้นหลังกล่องข้อความ
  myGLCD.print("DISTANCE ", CENTER, 48); // Prints the string
  void loop() { 
  // Home Screen
  if (currentPage == '0') {
    if (myTouch.dataAvailable()) {
      myTouch.read();
      x=myTouch.getX(); // X coordinate where the screen has been pressed
      y=myTouch.getY(); // Y coordinates where the screen has been pressed

      // ถ้ากดปุ่ม Sensor
      if ((x>=35) && (x<=285) && (y>=90) && (y<=130)) {
        drawFrame(35, 90, 285, 130); // กดปุ่ม
        currentPage = '1'; // Indicates that we are the first example
        myGLCD.clrScr(); // Clears the screen
        drawDistanceSensor(); //ถ้าคำสั่งนี้เป็นเท็จ funtion นี้จะไม่ถูกเรียก
}
    // Distance Sensor Example
  if (currentPage == '1') {    
      getDistance(); // Gets distance from the sensor and this function is repeatedly called while we are at the first example in order to print the lasest results from the distance sensor
      if (myTouch.dataAvailable()) {
        myTouch.read();
        x=myTouch.getX();
        y=myTouch.getY();
       
        // If we press the Centimeters Button
        if ((x>=10) && (x<=135) &&(y>=90) && (y<=163)) {
          selectedUnit = '0';
        }
        // If we press the Inches Button
        if ((x>=10) && (x<=135) &&(y>=173) && (y<=201)) {
          selectedUnit = '1';
        }
        // If we press the Back Button
        if ((x>=10) && (x<=60) &&(y>=10) && (y<=36)) {
          drawFrame(10, 10, 60, 36);
          currentPage = '0'; // Indicates we are at home screen
          myGLCD.clrScr();
          drawHomeScreen(); // Draws the home screen
        }
      }
  }
  // RGB LED Control 
  if (currentPage == '2') {
    setLedColor();
    if (myTouch.dataAvailable()) {
        myTouch.read();
        x=myTouch.getX();
        y=myTouch.getY();
        
        //Back button
        if ((x>=10) && (x<=60) &&(y>=10) && (y<=36)) {
          drawFrame(10, 10, 60, 36);
          currentPage = '0';
          myGLCD.clrScr();
          drawHomeScreen();
          // Turns the LED off
          analogWrite(redLed, 0);
          analogWrite(greenLed, 0);
          analogWrite(blueLed, 0);
        }
    }
  }
  // drawHomeScreen - Custom Function
void drawHomeScreen() {
  // Title
  myGLCD.setBackColor(0,0,0); // Sets the background color of the area where the text will be printed to black
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.setFont(BigFont); // Sets font to big
  myGLCD.print("Arduino TFT Tutorial", CENTER, 10); // Prints the string on the screen
  myGLCD.setColor(255, 0, 0); // Sets color to red
  myGLCD.drawLine(0,32,319,32); // Draws the red line
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.setFont(SmallFont); // Sets the font to small
  myGLCD.print("by HowToMechatronics.com", CENTER, 41); // Prints the string
  myGLCD.setFont(BigFont);
  myGLCD.print("Select Example", CENTER, 64);
  
  // Button - Distance Sensor
  myGLCD.setColor(16, 167, 103); // Sets green color
  myGLCD.fillRoundRect (35, 90, 285, 130); // Draws filled rounded rectangle
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.drawRoundRect (35, 90, 285, 130); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD.setFont(BigFont); // Sets the font to big
  myGLCD.setBackColor(16, 167, 103); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.print("DISTANCE SENSOR", CENTER, 102); // Prints the string
  
  // Button - RGB LED Control
  myGLCD.setColor(16, 167, 103);
  myGLCD.fillRoundRect (35, 140, 285, 180);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (35, 140, 285, 180);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(16, 167, 103);
  myGLCD.print("RGB LED CONTROL", CENTER, 152);
}
//====================================================
void drawDistanceSensor() {
  myGLCD.setColor(100, 155, 203);
  myGLCD.fillRoundRect (10, 10, 60, 36);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (10, 10, 60, 36);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(100, 155, 203);
  myGLCD.print("<-", 18, 15);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setFont(SmallFont);
  myGLCD.print("Back to Main Menu", 70, 18);
  myGLCD.setFont(BigFont);
  myGLCD.print("Ultrasonic Sensor", CENTER, 50);
  myGLCD.print("HC-SR04", CENTER, 76);
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawLine(0,100,319,100);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(SmallFont);
  myGLCD.print("Select Unit", 10, 114);
  myGLCD.setFont(BigFont);
  myGLCD.print("Distance:", 130, 120);
  myGLCD.setColor(223, 77, 55);
  myGLCD.fillRoundRect (10, 135, 90, 163);
  myGLCD.setColor(225, 255, 255);
  myGLCD.drawRoundRect (10, 135, 90, 163);
  myGLCD.setBackColor(223, 77, 55);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("cm", 33, 140);
  myGLCD.setColor(223, 77, 55);
  myGLCD.fillRoundRect (10, 173, 90, 201);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (10, 173, 90, 201);
  myGLCD.setBackColor(223, 77, 55);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("inch", 17, 180);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setFont(SmallFont);
  myGLCD.print("Source code at: HowToMechatronics.com", CENTER, 220);  
}
//====================================================
//===== getDistance - Custom Function
void getDistance() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distanceCm= duration*0.034/2;
  distanceInch= distanceCm/2.53;
  // Prints the distance in centimeters
  if (selectedUnit == '0' && distanceCm <=400) {
    myGLCD.setFont(SevenSegNumFont);
    myGLCD.setColor(0, 255, 0);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.printNumI(distanceCm,130, 145, 3,'0');
    myGLCD.setFont(BigFont);
    myGLCD.print("cm  ", 235, 178);
  
  }
  // Prints the distance in inches
  if (selectedUnit == '1' && distanceCm <=160) {
    myGLCD.setFont(SevenSegNumFont);
    myGLCD.setColor(0, 255, 0);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.printNumI(distanceInch,130, 145, 3,'0');
    myGLCD.setFont(BigFont);
    myGLCD.print("inch", 235, 178);
  } 
  delay(10);
}
//====================================================
void drawLedControl() {
  myGLCD.setColor(100, 155, 203);
  myGLCD.fillRoundRect (10, 10, 60, 36);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (10, 10, 60, 36);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(100, 155, 203);
  myGLCD.print("<-", 18, 15);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setFont(SmallFont);
  myGLCD.print("Back to Main Menu", 70, 18);
  myGLCD.setFont(BigFont);
  myGLCD.print("RGB LED Control", CENTER, 50);
  myGLCD.print("LED Color:", 10, 95);
  myGLCD.print("R", 10, 135);
  myGLCD.print("G", 10, 175);
  myGLCD.print("B", 10, 215);
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawLine(0,75,319,75); 
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRect(30, 138, 310, 148); // R - Slider
  myGLCD.drawRect(30, 178, 310, 188);
  myGLCD.drawRect(30, 218, 310, 228);  
}
//====================================================
//============= setLedColor() - Custom Funtion
void setLedColor() {
  if (myTouch.dataAvailable()) {
    myTouch.read();
    x=myTouch.getX();
    y=myTouch.getY();        
    // Area of the Red color slider
    if( (y>=130) && (y<=156)) {
      xR=x; // Stores the X value where the screen has been pressed in to variable xR
      if (xR<=38) { // Confines the area of the slider to be above 38 pixels
        xR=38;
      }
      if (xR>=303){ /// Confines the area of the slider to be under 310 pixels
        xR=303;
      }
    }
    // Area of the Green color slider
    if( (y>=170) && (y<=196)) {
      xG=x;
      if (xG<=38) {
        xG=38;
      }
      if (xG>=303){
        xG=303;
      }
    }
    // Area of the Blue color slider
    if( (y>=210) && (y<=236)) {
      xB=x;
      if (xB<=38) {
        xB=38;
      }
      if (xB>=303){
        xB=303;
      }
    }    
  }
  // Maps the values of the X - Axis from 38 to 0 and 310 to 255, because we need values from 0 to 255 for turning on the led
  int xRC = map(xR,38,310,0,255);
  int xGC = map(xG,38,310,0,255);
  int xBC = map(xB,38,310,0,255);
  
  // Sends PWM signal to the pins of the led
  analogWrite(redLed, xRC);
  analogWrite(greenLed, xGC);
  analogWrite(blueLed, xBC);
  
  // Draws a rectangle with the latest color combination 
  myGLCD.setColor(xRC, xGC, xBC);
  myGLCD.fillRoundRect(175, 87, 310, 119);
  
  // Draws the positioners
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(xR,139,(xR+4),147); // Positioner
  myGLCD.setColor(xRC, 0, 0);
  myGLCD.fillRect(31, 139, (xR-1), 147);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect((xR+5), 139, 309, 147);
  
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(xG,179,(xG+4),187);
  myGLCD.setColor(0, xGC, 0);
  myGLCD.fillRect(31, 179, (xG-1), 187);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect((xG+5), 179, 309, 187);
  
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(xB,219,(xB+4),227);
  myGLCD.setColor(0, 0, xBC);
  myGLCD.fillRect(31, 219, (xB-1), 227);
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect((xB+5), 219, 309, 227);
}
//====================================================
void drawGround() {
  myGLCD.setColor(221,216,148);
  myGLCD.fillRect(0, 215, 319, 239);
  myGLCD.setColor(47,175,68);
  myGLCD.fillRect(0, 205, 319, 214);
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(221, 216, 148);
  myGLCD.setFont(BigFont);
  myGLCD.print("Score:",5,220);
  myGLCD.setFont(SmallFont);
  myGLCD.print("HowToMechatronics.com", 140, 220); 
}
void drawPilars(int x, int y) {
   
    if (x>=270){
      myGLCD.setColor(0, 200, 20);
      myGLCD.fillRect(318, 0, x, y-1);
      myGLCD.setColor(0, 0, 0);
      myGLCD.drawRect(319, 0, x-1, y);
      myGLCD.setColor(0, 200, 20);
      myGLCD.fillRect(318, y+81, x, 203);
      myGLCD.setColor(0, 0, 0);
      myGLCD.drawRect(319, y+80, x-1, 204); 
    }
    else if( x<=268) {
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRect(x+51, 0, x+53, y);
    myGLCD.setColor(0, 200, 20);
    myGLCD.fillRect(x+49, 1, x+1, y-1);
    myGLCD.setColor(0, 0, 0);
    myGLCD.drawRect(x+50, 0, x, y);
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRect(x-1, 0, x-3, y);
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRect(x+51, y+80, x+53, 204);
    myGLCD.setColor(0, 200, 20);
    myGLCD.fillRect(x+49, y+81, x+1, 203);
    myGLCD.setColor(0, 0, 0);
    myGLCD.drawRect(x+50, y+80, x, 204);
    myGLCD.setColor(114, 198, 206);
    myGLCD.fillRect(x-1, y+80, x-3, 204);
  }
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(221, 216, 148);
  myGLCD.setFont(BigFont);
  myGLCD.printNumI(score, 100, 220);
}



