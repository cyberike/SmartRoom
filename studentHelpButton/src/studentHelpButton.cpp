/* 
 * Project: studentHelpButton
 * Author: Isaac Martinez Sr. 
 * Date: 3-4-24
 */

#include "Particle.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE (SEMI_AUTOMATIC);

//Variables Declared
int i;
int buttonStatus1 = 0; 
int buttonStatus2 = 0;
int buttonStatus3 = 0;
int openCookieJar;
int closeCookieJar;

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


//Declare Objects
Servo myServo; // Declares the servo object globally

//button_click HELPBUTTON (D8);
//button_click GETBACKTOWORK ( D9);
//button_click VACATION (D16);

void setup() {
  Serial.begin(9600);
  pinMode (HELPBUTTONPIN, INPUT_PULLUP);
  pinMode (GETBACKTOWORKPIN, INPUT_PULLUP);
  pinMode (VACATIONPIN, INPUT_PULLUP);

  pinMode (LEDPIN, OUTPUT);
  pinMode (LAVAPIN, OUTPUT);
  pinMode (FANPIN, OUTPUT);
  pinMode (BUZZERPIN, OUTPUT);
  pinMode (DINGPIN, OUTPUT);
  pinMode (SERVOPIN, OUTPUT);
  myServo.attach(SERVOPIN);
 //  Put initialization like pinMode and begin functions here
}

void loop() {
  buttonStatus1 = digitalRead(HELPBUTTONPIN);
  buttonStatus2 = digitalRead(GETBACKTOWORKPIN);
  buttonStatus3 = digitalRead(VACATIONPIN);// Reads the current state of the button

  if (buttonStatus1 == LOW){
    digitalWrite(LEDPIN, HIGH);
    Serial.printf("s = %s\n","Help button pressed, Instructor notiifed.");
  }
  if (buttonStatus2 == LOW) {
    digitalWrite (LEDPIN, LOW);
    Serial.printf("s =%s\n", "Back To Work");
  }
  if (buttonStatus3 == LOW) {
    openCookieJar ();
    digitalWrite (FANPIN, HIGH);
    digitalWrite (LAVAPIN, LOW);
    Serial.printf("s = %s\n", "Don't Worry Be Happy!");
  }
  for (int pos = 0; pos <= 180; pos += 1) { // Moves the servo from 0 to 180
    myServo.write(pos); // Tells the servo to go to position in variable pos
    delay(15); // Gives the servo 15ms to reach the position
    }{
    delay(1000); // Wait for 1 sec
    myServo.write(0); // Returns the servo to the starting point
  }
  else if() {
    int closeCookieJar;
    closeCookieJar();
    digitalWrite(FANPIN, LOW);
    digitalWrite(LAVAPIN, LOW);
  }
}
int openCookieJar;
void openCookieJar(){
  myServo.write(0);
  delay(1000);
}
void closeCookieJar(){
  myServo.write(0);
  delay(1000);

}
  