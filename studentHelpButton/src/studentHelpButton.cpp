/*
 * Project: studentHelpButton
 * Author: Isaac Martinez Sr.
 * Date: 3-4-24
 */

#include "Particle.h"
#include "IoTClassroom_CNM.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "IoTTimer.h"
#include "wemo.h"
#include "hue.h"

SYSTEM_MODE(MANUAL); //control logging into classroom router

//Variables Declared
int i;
bool buttonOnOff = false;
bool vacationMode = false;
int color;

char studentName [] ={"Isaac"};

//Constants Declared/Defined
//const int HELPBUTTONPIN = D8; 
//const int GETBACKTOWORKPIN = D9;
//const int VACATIONPIN = D16;
const int LEDPIN = SCL;
const int SERVOPIN = D15;
const int LAVAPIN = D17;
const int FANPIN = D18;
const int BUZZERPIN = D19;
const int DINGPIN = D14;
const int MYWEMO = 1;
const int BULB = 6;
const int BRIGHTNESS = 100;
const int initDing =3000;
const int recurDing =300000;



//Declare Objects
Servo myServo; // Declares the servo object globally
Adafruit_SSD1306 display(-1);
IoTTimer buzzerTimer;
IoTTimer startDingTimer;
Button helpButton(D8);
Button backToWorkButton(D9);
Button vacationButton(D16);
// class, object, (pin/sometime nothing)
// Function prototypes
void openCookieJar();
void closeCookieJar();
//void displaySplashScreen();
void buzzerCallback();
void dingCallback();

void setup() {
  Serial.begin(9600);
  WiFi.on();
  WiFi.clearCredentials();
  WiFi.setCredentials("IoTNetwork");
  WiFi.connect();
  while(WiFi.connecting()) {
    Serial.printf("Lets Go!!!!");
  }

  pinMode(LEDPIN, OUTPUT);
  //pinMode(LAVAPIN, OUTPUT);
  //pinMode(FANPIN, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(DINGPIN, OUTPUT);
  pinMode(SERVOPIN, OUTPUT);
  myServo.attach(SERVOPIN);

  // Initialize OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(2);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.clearDisplay();
  display.display();
  delay(2000);
  display.println("Student Help Button");
  display.println("By Isaac Martinez Sr.");
  display.display();
  delay(2000);
  display.clearDisplay();

  // Initialize Ding
}

void loop() {
    
  if (helpButton.isClicked()) {
    display.setCursor(0, 0);
    setHue(BULB, true, HueRed, BRIGHTNESS, 255);
    Serial.printf("Help button pressed, Instructor notified %s is now in the que\n",studentName);
    display.printf("Help button pressed, Instructor notified %s is now in the que\n",studentName);
    tone(DINGPIN,4186,2000); 
    Serial.printf("Buzzer on\n");
    startDingTimer.startTimer(recurDing);
    display.display();
    display.clearDisplay();

  } 
    if(startDingTimer.isTimerReady()){
      tone(DINGPIN,4186,3000); 
      startDingTimer.startTimer(recurDing);
    }
       if (backToWorkButton.isClicked()) {
        display.setCursor(0, 0);
    setHue(BULB, false, HueRed, BRIGHTNESS, 255);
        display.setCursor(0, 0);
    display.printf("Get Back To Work!,%s has been saved.\n",studentName);

    }
   
  if (vacationButton.isClicked()){
    buttonOnOff =! buttonOnOff; 
  }
  if(buttonOnOff){
    display.setCursor(0, 0);
    wemoWrite (MYWEMO, HIGH);
    openCookieJar();
    display.setCursor(0, 0);
display.printf("Test Message\n");
    display.display();


   // Serial.printf("Don't Worry Be Happy!");
   // display.printf("Don't Worry Be Happy!");
}
  else{ 
    display.setCursor(0, 0);
    wemoWrite(MYWEMO,LOW);
    closeCookieJar();
  }
  }
  


   


    


//   // Control Hue light based on help button state
//   if (buttonOnOff) {
//     setHue(BULB, true, HueRainbow[color % 7], BRIGHTNESS, 255);
//   } else {
//     setHue(BULB, false, HueRainbow[color % 7], BRIGHTNESS, 255);
//   }

// }

void openCookieJar(){
  myServo.write(360);
  //delay (1000);
}

void closeCookieJar() {
  myServo.write(0);
  //delay(1000);
}

void buzzerCallback() {
  digitalWrite(BUZZERPIN, HIGH);
  delay(1000);
  digitalWrite(BUZZERPIN, LOW);
}

void dingCallback() {
  if (buttonOnOff) {
    digitalWrite(DINGPIN, HIGH);
    delay(500);
    digitalWrite(DINGPIN, LOW);
  }
}
