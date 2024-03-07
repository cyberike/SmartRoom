/*
 * Project: Student Help Button
 * Author: Isaac Martinez Sr.
 * Date: 3-4-24
 * Description: This project is designed to help students notify instructors when they need assistance, 
 * and also includes features like vacation mode for automatic handling of certain tasks.
 */

#include "Particle.h"
#include "IoTClassroom_CNM.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "IoTTimer.h"
#include "wemo.h"
#include "hue.h"

SYSTEM_MODE(MANUAL); // Controls logging into classroom router without using automatic connection

// Variable Declarations
char studentName[] = "Isaac";
bool buttonOnOff = false;
bool vacationMode = false;



// Pin Constants
const int LEDPIN = SCL;
const int SERVOPIN = D15;
const int BUZZERPIN = D19;
const int DINGPIN = D14;
const int MYWEMO = 1;
const int BULB = 6;
const int BRIGHTNESS = 100;
const int recurDing = 300000;

// Object Declarations
Servo myServo;
Adafruit_SSD1306 display(-1);
IoTTimer startDingTimer;
Button helpButton(D8);
Button backToWorkButton(D9);
Button vacationButton(D16);

// Function prototypes
void closeCookieJar();
//void displaySplashScreen();
void buzzerCallback();
void dingCallback();
void openCookieJar();

void setup() {
  Serial.begin(9600);

  // Initialize Wi-Fi connection
  WiFi.on();
  WiFi.clearCredentials();
  WiFi.setCredentials("IoTNetwork");
  WiFi.connect();
  while (WiFi.connecting()) {
    Serial.print("Connecting to WiFi...");
  }
  Serial.println("Connected!");

  // Pin Modes
  pinMode(LEDPIN, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(DINGPIN, OUTPUT);
  pinMode(SERVOPIN, OUTPUT);

  // Attach servo
  myServo.attach(SERVOPIN);

  
  


  // Initialize OLED Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(2);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Student Help Button");
  display.println("By Isaac Martinez Sr.");
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  // Help Button Pressed
  if (helpButton.isClicked()) {
    display.printf("Help button pressed, Instructor notified. You are now in the queue.");
    display.display();
    setHue(BULB, true, HueRed, BRIGHTNESS, 255);
    tone(DINGPIN, 4186, 2000); // Play a tone for notification
    startDingTimer.startTimer(recurDing);
    display.clearDisplay();

  }

  // Repeat Notification
  if (startDingTimer.isTimerReady()) {
    tone(DINGPIN, 4186, 3000);
    startDingTimer.startTimer(recurDing);
  }

  // Back to Work Button Pressed
  if (backToWorkButton.isClicked()) {
    display.printf("Get Back To Work! You have been saved.");
    display.display();
    setHue(BULB, false, HueRed, BRIGHTNESS, 255);
  }

  // Vacation Mode Toggle
  if (vacationButton.isClicked()) {
    buttonOnOff = !buttonOnOff;
    if (buttonOnOff) {
      wemoWrite(MYWEMO, HIGH);
      openCookieJar();
      display.printf("Vacation mode ON. Enjoy your break!");
    } else {
      wemoWrite(MYWEMO, LOW);
      closeCookieJar();
      display.printf("Vacation mode OFF. Welcome back!");
    }
  }
}

 void openCookieJar() {
  myServo.write(360); // Open the jar
}

void closeCookieJar() {
  myServo.write(0); // Close the jar
}

void displayMessage(const char* message) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(message);
  display.display();
}
