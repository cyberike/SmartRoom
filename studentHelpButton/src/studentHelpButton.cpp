/* 
 * Project: studentHelpButton
 * Author: Isaac Martinez Sr. 
 * Date: 3-4-24
 */
 // Include Particle Device OS APIs
#include "Particle.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE (SEMI_AUTOMATIC);

//Variables Declared
int i ;

//Constants Declared/Defined 
const int HELPBUTTON = D8;
const int GETBACKTOWORK = D9;
const int VACATION = D16;
const int LEDPIN = SCL;
const int SERVOPIN = D15;
const int LAVAPIN = D17;
const int FANPIN = D18;
const int BUZZERPIN = D19;
const int DINGPIN = D14;


//Declare Objects

button_click HELPBUTTON (D8);
button_click GETBACKTOWORK ( D9);
button_click VACATION (D16);

// setup() runs once, when the device is first turned on
void setup() {
 //  Put initialization like pinMode and begin functions here
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

  // Example: Publish event to cloud every 10 seconds. Uncomment the next 3 lines to try it!
  // Log.info("Sending Hello World to the cloud!");
  // Particle.publish("Hello world!");
  // delay( 10 * 1000 ); // milliseconds and blocking - see docs for more info!
}
