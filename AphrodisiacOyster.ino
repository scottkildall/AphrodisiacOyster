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
      
void setup() {
  //-- set our two pins to output
  pinMode(PERISTALTIC_PUMP, OUTPUT);
  pinMode(SELF_PRIMING_PUMP, OUTPUT);

  //-- Blink LEDs 3 times upon startup
  //-- we might want to change this later to have a LED indicating power only
  for( int i = 0; i < 3; i++ ) {
    digitalWrite(PERISTALTIC_PUMP, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(250);                       // wait for a second
    digitalWrite(PERISTALTIC_PUMP, LOW);    // turn the LED off by making the voltage LOW
    delay(250);   
  }
}

//-- track button input and activate the appropriate LED/motor
void loop() {
  digitalWrite(PERISTALTIC_PUMP, HIGH);  
  digitalWrite(SELF_PRIMING_PUMP, LOW);
  delay(1000);                       
  digitalWrite(PERISTALTIC_PUMP, LOW);   
  digitalWrite(SELF_PRIMING_PUMP, HIGH);
  delay(1000);     
}
