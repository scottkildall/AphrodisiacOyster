/*
  Aphrodisiac Oyster
  A project by Stephanie Rothenberg in consultation with Scott Kildall

  Motor controller that uses two momentary switches to turn two motors
  on and off through a Darlington transitor (ULN2803). Each channel of the
  transistor is also connected in parallel to an LED.
*/

// Leave uncommented if we are using the Circuit Playground chip, otherwise comment
// out the #define below
//#define CIRCUIT_PLAYGROUND

#ifdef CIRCUIT_PLAYGROUND
  #include <Adafruit_CircuitPlayground.h>
#endif

#include "MSTimer.h"

//========== PIN NUMBERS for the two pumps + LEDs that run in parallel ============
#define PERISTALTIC_PUMP (6)
#define SELF_PRIMING_PUMP (12)
#define AIR_PUMP (3)

#define PERISTALTIC_BUTTON (10)
#define SELF_PRIMING_BUTTON (9)
#define AIR_BUTTON (2)

//========== TIMERS for the Interaction ============
// Timer Variables
MSTimer standbyTimer;
MSTimer chipPattern1Timer;
MSTimer chipPattern2Timer;
MSTimer waterPumpOnTimer;
MSTimer airPumpOnTimer;
MSTimer peristalticPumpOnTimer;

// how long for each timer
#define STANDBY_TIMER_MS (60 * 1000)
#define CHIPPATTERN1_TIMER_MS (5 * 1000)
#define CHIPPATTERN2_TIMER_MS (5 * 1000)
#define WATERPUMPON_TIMER_MS (10 * 1000)
#define AIRPUMPON_TIMER_MS (10 * 1000)
#define PERISTALTICPUMPON_TIMER_MS (5 * 1000)

//========== STATES for the Interaction ============
int state;      // this global variable for interaction state

// constants for each state (more readable than #define)
const int kStateStandby = 0;
const int kStateChipPattern1 = 1;     // dispense
const int kStateChipPattern2 = 2;     // auto-cycle
const int kStateWaterPumpOn = 3;
const int kStatePeristalticPumpOn = 4;

//========== STATES for Light Patterns ============
int lightPatternNum;      // this global variable for interaction state

// constants for each light pattern 
const int kLightPatternStandby = 1000;
const int kLightPatternButtonPressed = 1001;
const int kLightPatternAutoCycle = 1002;
const int kLightPatternDispense = 1003;


// global variables for color and brightness for Neopixels
int r = 255;
int g = 255;
int b = 255;
int brightness = 128;
int brightDir = 1;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Aphrodisiac Oyster");

  #ifdef CIRCUIT_PLAYGROUND
    CircuitPlayground.begin();
  #endif 
   
  //-- set our two pins to output
  pinMode(PERISTALTIC_PUMP, OUTPUT);
  pinMode(SELF_PRIMING_PUMP, OUTPUT);
  pinMode(AIR_PUMP, OUTPUT);

  pinMode(PERISTALTIC_BUTTON, INPUT);
  pinMode(SELF_PRIMING_BUTTON, INPUT);
  pinMode(AIR_BUTTON, INPUT);


  //-- Blink LEDs 3 times upon startup
  //-- we might want to change this later to have a LED indicating power only
  /*for( int i = 0; i < 3; i++ ) {
    digitalWrite(PERISTALTIC_PUMP, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second
    digitalWrite(PERISTALTIC_PUMP, LOW);    // turn the LED off by making the voltage LOW
    delay(100);   
  }*/

  #ifdef CIRCUIT_PLAYGROUND
    for( int i = 0; i < 5; i++ ) {
      CircuitPlayground.redLED(HIGH);
      delay(100);
      CircuitPlayground.redLED(LOW);
      delay(100);   
    }
    CircuitPlayground.redLED(HIGH);

    // 10 built-in NeoPixels, set all to blue
    for( int i = 0; i < 10; i++ ) {
      CircuitPlayground.setPixelColor(i, 0,0,255);
    }
  #endif

  setupTimers();

  // set initial state to standby mode
  setState(kStateStandby);
}

//-- track button input and activate the appropriate LED/motor
void loop() {

  //-- Interactive mode for all buttons (for testing)
  checkPeristalticPump();
  checkSelfPrimingPump();
  checkAirPump();

  // check dispense button to see if it was pressed
  // (code would go here)
  
  // check timers to see if the states have changed
  // (code would go here)
  
  // update light patterns based on the light pattern number
  updateLightPattern();
}

//-- initializes all the timers (in milliseconds) using the #define variables
void setupTimers() {
  standbyTimer.setTimer(STANDBY_TIMER_MS);
  chipPattern1Timer.setTimer(CHIPPATTERN1_TIMER_MS);
  chipPattern2Timer.setTimer(CHIPPATTERN2_TIMER_MS);
  waterPumpOnTimer.setTimer(WATERPUMPON_TIMER_MS);
  airPumpOnTimer.setTimer(AIRPUMPON_TIMER_MS);
  peristalticPumpOnTimer.setTimer(PERISTALTICPUMPON_TIMER_MS);
}

//-- change the state of the machine, use if instead of switch for readability
//-- we will activate different light patterns, depending on the state
//-- we will turn pumps on/off, depending on the state
void setState(const int newState) {
  if( newState == kStateStandby ) {
     standbyTimer.start();
     lightPatternNum = kLightPatternStandby;
  }
  else if( newState == kStateChipPattern1 ) {
     chipPattern1Timer.start();
     lightPatternNum = kLightPatternAutoCycle;
  }
  else if( newState == kStateChipPattern2 ) {
     chipPattern2Timer.start();
     lightPatternNum = kLightPatternButtonPressed;
  }
  else if( newState == kStateWaterPumpOn ) {
     waterPumpOnTimer.start();
     //-- keep same light pattern as the chip cycle
  }
  else if( newState == kStatePeristalticPumpOn ) {
     peristalticPumpOnTimer.start();
     lightPatternNum = kLightPatternDispense;
  }
}

//-- check to see if the peristaltic button is being pressed and then turn on that pump
void checkPeristalticPump() {
  // Check for peristanlic pump on/off
  // (code will be more precise, later — add debounce)
  boolean pumpOn = digitalRead(PERISTALTIC_BUTTON);
  if( pumpOn )
    digitalWrite(PERISTALTIC_PUMP, HIGH); 
  else  
    digitalWrite(PERISTALTIC_PUMP, LOW);  
}

//-- check to see if the peristaltic button is being pressed and then turn on that pump
void checkSelfPrimingPump() {
  // Check for self-priming pump on/off
  // (code will be more precise, later — add debounce)
  boolean pumpOn = digitalRead(SELF_PRIMING_BUTTON);
  if( pumpOn )
    digitalWrite(SELF_PRIMING_PUMP, HIGH); 
  else  
    digitalWrite(SELF_PRIMING_PUMP, LOW);  
}

//-- check to see if the air button is being pressed and then turn on that pump
void checkAirPump() {
  // Check for self-priming pump on/off
  // (code will be more precise, later — add debounce)
  boolean pumpOn = digitalRead(AIR_BUTTON);
  if( pumpOn )
    digitalWrite(AIR_PUMP, HIGH); 
  else  
    digitalWrite(AIR_PUMP, LOW);  
}

//-- looks at the light pattern number and will update the Neopixels on the Circuit Playground board
void updateLightPattern() {
  if( lightPatternNum == kLightPatternStandby )
    adjustStandbyLightPattern();
 
  // global change using brightness and the r,g, b global variables
  // all NeoPixels will do the same exact thing
  #ifdef CIRCUIT_PLAYGROUND
    CircuitPlayground.setBrightness(brightness);
      for( int i = 0; i < 10; i++ ) {
      CircuitPlayground.setPixelColor(i, r, g, b);
    }
  #endif
}

// pulsating blue pattern
void adjustStandbyLightPattern() {
  r = 0;
  g = 0;
  b = 255;
  
  brightness = brightness + brightDir;

  if( brightness < 128 ) {
    brightness = 128;
    brightDir = 1;    // start fading up
  }
  else if( brightness > 255 ) {
    brightness = 255;
    brightDir = -1;   // start fading down
  } 

  delay(20);
}
