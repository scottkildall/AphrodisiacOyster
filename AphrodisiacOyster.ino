/*
  Aphrodisiac Oyster
  A project by Stephanie Rothenberg in consultation with Scott Kildall

  Motor controller that uses two momentary switches to turn two motors
  on and off through a Darlington transitor (ULN2803). Each channel of the
  transistor is also connected in parallel to an LED.
*/

//-- pin numbers for the two pumps + LEDs that run in parallel
#define PERISTALTIC_PUMP (4)
#define SELF_PRIMING_PUMP (16)

#define PERISTALTIC_BUTTON (5)
#define SELF_PRIMING_BUTTON (10)
      
void setup() {
  Serial.begin(115200);
  Serial.println("Starting Aphrodisiac Oyster");
  
  //-- set our two pins to output
  pinMode(PERISTALTIC_PUMP, OUTPUT);
  pinMode(SELF_PRIMING_PUMP, OUTPUT);

  pinMode(PERISTALTIC_BUTTON, INPUT);
  pinMode(SELF_PRIMING_BUTTON, INPUT);

  //-- Blink LEDs 3 times upon startup
  //-- we might want to change this later to have a LED indicating power only
  for( int i = 0; i < 3; i++ ) {
    digitalWrite(PERISTALTIC_PUMP, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second
    digitalWrite(PERISTALTIC_PUMP, LOW);    // turn the LED off by making the voltage LOW
    delay(100);   
  }
}

//-- track button input and activate the appropriate LED/motor
void loop() {
  checkPeristalticPump();
}

//-- check to see if the peristaltic button is being pressed and then turn on that pump
void checkPeristalticPump() {
  // Check for peristantlic pump on/off
  // (code will be more precise, later — add debounce)
  boolean persistalticPumpOn = digitalRead(PERISTALTIC_BUTTON);
  if( persistalticPumpOn )
    digitalWrite(PERISTALTIC_PUMP, HIGH); 
  else  
    digitalWrite(PERISTALTIC_PUMP, LOW);  
}
