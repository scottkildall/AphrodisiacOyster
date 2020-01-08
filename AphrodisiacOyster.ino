/*
  Aphrodisiac Oyster
  A project by Stephanie Rothenberg in consultation with Scott Kildall

  Motor controller that uses two momentary switches to turn two motors
  on and off through a Darlington transitor (ULN2803). Each channel of the
  transistor is also connected in parallel to an LED.
*/

#include <Adafruit_CircuitPlayground.h>

//-- pin numbers for the two pumps + LEDs that run in parallel
#define PERISTALTIC_PUMP (6)
#define SELF_PRIMING_PUMP (12)

#define PERISTALTIC_BUTTON (10)
#define SELF_PRIMING_BUTTON (9)

// global var for brightness for Neopixels
int brightness = 255;
int brightDir = -1;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Aphrodisiac Oyster");

  CircuitPlayground.begin();
   
  //-- set our two pins to output
  pinMode(PERISTALTIC_PUMP, OUTPUT);
  pinMode(SELF_PRIMING_PUMP, OUTPUT);

  pinMode(PERISTALTIC_BUTTON, INPUT);
  pinMode(SELF_PRIMING_BUTTON, INPUT);

  //-- Blink LEDs 3 times upon startup
  //-- we might want to change this later to have a LED indicating power only
  /*for( int i = 0; i < 3; i++ ) {
    digitalWrite(PERISTALTIC_PUMP, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second
    digitalWrite(PERISTALTIC_PUMP, LOW);    // turn the LED off by making the voltage LOW
    delay(100);   
  }*/

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
}

//-- track button input and activate the appropriate LED/motor
void loop() {
  checkPeristalticPump();
  checkSelfPrimingPump();

  // add later for pulsating effect
 // adjustBrightness();
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

/*
void adjustBrightness() {
  brightness += brightDir;
  if(  brightness < 0 ) {
    brightness = 0;
    brightDir = -brightDir;
  }
  else if( brightness > 255 ) {
    brightness = 255;
    brightDir = -brightDir;
  } 

  CircuitPlayground.setBrightness(brightness);
}
*/
