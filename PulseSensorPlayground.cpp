/*
 * A central Playground object to exercise the PulseSensor.
 * See https://www.pulsesensor.com to get started.
 *
 * This software is not intended for medical use.
 */
#include <PulseSensorPlayground.h>




/*
* begin() function checks for supported hardware
* and sets the correct intterupt registers
* for 2mS sample rate
*
*/
void PulseSensorPlayground::begin() { 
  begin(1);
}

void PulseSensorPlayground::begin(int numPS) {
  for(int i=0; i<numPS; i++){
    pinMode(blinkPin[i],OUTPUT);
    pinMode(blinkPin[i],LOW);
    pinMode(fadePin[i],OUTPUT);
    analogWrite(fadePin[i],0);
  }

  #if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
    // Initializes Timer1 to throw an interrupt every 2mS.
    // Interferes with PWM on pins 9 and 10
    TCCR1A = 0x00; // DISABLE OUTPUTS AND PWM ON DIGITAL PINS 9 & 10
    TCCR1B = 0x11; // GO INTO 'PHASE AND FREQUENCY CORRECT' MODE, NO PRESCALER
    TCCR1C = 0x00; // DON'T FORCE COMPARE
    TIMSK1 = 0x01; // ENABLE OVERFLOW INTERRUPT (TOIE1)
    #if F_CPU == 16000000L   //  if using 16MHz crystal
      ICR1 = 16000;  // TRIGGER TIMER INTERRUPT EVERY 2mS
    #elif F_CPU == 8000000L  // if using 8MHz crystal
      ICR1 = 8000;   // TRIGGER TIMER INTERRUPT EVERY 2mS
    #endif
    uno = true;
    sei();  // enable global interrupts
  #elif defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__)
    // Initializes Timer1 to throw an interrupt every 2mS.
    // Interferes with PWM on pins 9 and 10
    TCCR1A = 0x00;
    TIMSK1 = 0x02;
    #if F_CPU == 16000000L
      TCCR1B = 0x0C; // prescaler = 256
      OCR1A = 0x7C;  // count to 124 for 2mS interrupt
    #elif F_CPU == 8000000L
      TCCR1B = 0x0B; // prescaler = 64
      OCR1A = 0xF9;  // count to 249 for 2mS interrupt
    #endif
    leo = true;
    sei();  // enable global interrupts
  #endif

}


void PulseSensorPlayground::sample_detect(){
  testBool = true;
}



ISR(TIMER1_OVF_vect)
{
  if(pulse.uno){ pulse.sample_detect(); }
}

ISR(TIMER1_COMPA_vect)
{
  if(pulse.leo){ pulse.sample_detect(); }
}

PulseSensorPlayground pulse;
