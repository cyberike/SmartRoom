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

SYSTEM_MODE(MANUAL); //control logging into classroom router

//Variables Declared
int i;
int buttonStatus1 = 0;
int buttonStatus2 = 0;
int buttonStatus3 = 0;
bool buttonOnOff = false;
bool vacationMode = false;
int color;

char studentName [] ={"Isaac"};

//Constants Declared/Defined
const int HELPBUTTONPIN = D8; 
const int GETBACKTOWORKPIN = D9;
const int VACATIONPIN = D16;
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

//const unsigned long BUZZER_INTERVAL = 3 * 60 * 60 * 1000; // 3 hours in milliseconds
//const unsigned long DING_INTERVAL = 5 * 60 * 1000; // 5 minutes in milliseconds


//Declare Objects
Servo myServo; // Declares the servo object globally
Adafruit_SSD1306 display(-1);
IoTTimer buzzerTimer;
IoTTimer startDingTimer;
Button helpButton(D8);
// class, object, (pin/sometime nothing)
// Function prototypes
void openCookieJar();
void closeCookieJar();
void displaySplashScreen();
void buzzerCallback();
void dingCallback();

void setup() {
  Serial.begin(9600);

  WiFi.on();
  WiFi.clearCredentials();
  WiFi.setCredentials("IoTNetwork");
  
  WiFi.connect();
  while(WiFi.connecting()) {
    Serial.printf(".");
  }
  Serial.printf("\n\n");

  pinMode(GETBACKTOWORKPIN, INPUT_PULLUP);
  pinMode(VACATIONPIN, INPUT_PULLUP);

  pinMode(LEDPIN, OUTPUT);
  pinMode(LAVAPIN, OUTPUT);
  pinMode(FANPIN, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(DINGPIN, OUTPUT);
  pinMode(SERVOPIN, OUTPUT);
  myServo.attach(SERVOPIN);

  // Initialize OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  displaySplashScreen();
  display.display();
  noTone(DINGPIN);
}

void loop() {
  buttonStatus2 = digitalRead(GETBACKTOWORKPIN);
  buttonStatus3 = digitalRead(VACATIONPIN);// Reads the current state of the button

  if (helpButton.isClicked()) {
    setHue(BULB, true, HueRed, BRIGHTNESS, 255);
    Serial.printf("Help button pressed, Instructor notified %s is now in the que\n",studentName);
    tone(DINGPIN,4186,3000); 
    Serial.printf("Buzzer on\n");
    startDingTimer.startTimer(recurDing);
  }
    if(startDingTimer.isTimerReady()){
      tone(DINGPIN,4186,3000); 
      startDingTimer.startTimer(recurDing);
    }


//   if (buttonStatus2 == LOW) {
//     buttonOnOff = false;
//     vacationMode = false;
//     digitalWrite(LEDPIN, LOW);
//     digitalWrite(FANPIN, LOW);
//     wemoWrite(MYWEMO, LOW); // Turn off the Wemo for lava lamp and fan
//     Serial.printf("s =%s\n", "Back To Work");
//     delay(1000);
//   }
//   if (buttonStatus3 == LOW) {
//     vacationMode = !vacationMode;
//     if (vacationMode) {
//       openCookieJar();
//       digitalWrite(FANPIN, HIGH);
//       wemoWrite(MYWEMO, HIGH); // Turn on the Wemo for lava lamp and fan
//       Serial.printf("s = %s\n", "Don't Worry Be Happy!");
//     } else {
//       closeCookieJar();
//       digitalWrite(FANPIN, LOW);
//       wemoWrite(MYWEMO, LOW); // Turn off the Wemo for lava lamp and fan
//     }
//     delay(1000);
//   }

//   // Control Hue light based on help button state
//   if (buttonOnOff) {
//     setHue(BULB, true, HueRainbow[color % 7], BRIGHTNESS, 255);
//   } else {
//     setHue(BULB, false, HueRainbow[color % 7], BRIGHTNESS, 255);
//   }

// }

// void openCookieJar() {
//   for (int pos = 0; pos <= 180; pos += 1) {
//     myServo.write(pos);
//     delay(15);
//   }
//   delay(1000);
}

void closeCookieJar() {
  myServo.write(0);
  delay(1000);
}

void displaySplashScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Student Help Button");
  display.println("by Isaac Martinez Sr.");
  display.display();
  delay(2000);
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