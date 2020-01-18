/*
  Aphrodisiac Oyster
  A project by Stephanie Rothenberg in consultation with Scott Kildall

  Motor controller that uses two momentary switches to turn two motors
  on and off through a Darlington transitor (ULN2803). Each channel of the
  transistor is also connected in parallel to an LED.
*/

// Leave uncommented if we are using the Circuit Playground chip, otherwise comment
// out the #define below
#define CIRCUIT_PLAYGROUND

#ifdef CIRCUIT_PLAYGROUND
  #include <Adafruit_CircuitPlayground.h>
#endif

//-- pin numbers for the two pumps + LEDs that run in parallel
#define PERISTALTIC_PUMP (6)
#define SELF_PRIMING_PUMP (12)
#define AIR_PUMP (3)

#define PERISTALTIC_BUTTON (10)
#define SELF_PRIMING_BUTTON (9)
#define AIR_BUTTON (2)

// global var for brightness for Neopixels
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
}

//-- track button input and activate the appropriate LED/motor
void loop() {
  checkPeristalticPump();
  checkSelfPrimingPump();
  checkAirPump();

  // add later for pulsating effect
  adjustBrightness();
  delay(20);
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


void adjustBrightness() {
  brightness = brightness + brightDir;
  if( brightness < 128 ) {
    brightness = 128;
    brightDir = 1;    // start fading up
  }
  else if( brightness > 255 ) {
    brightness = 255;
    brightDir = -1;   // start fading down
  } 

  #ifdef CIRCUIT_PLAYGROUND
    CircuitPlayground.setBrightness(brightness);
      for( int i = 0; i < 10; i++ ) {
      CircuitPlayground.setPixelColor(i, 0,0,255);
    }
  #endif
}
