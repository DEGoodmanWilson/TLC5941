#include <avr/interrupt.h>
#include "LEDISR.h"

/// This is the Interrupt Service Routine (ISR) for Timer1 compare match.
uint16_t gsclk_counter;
uint16_t half_period;

ISR(TIMER1_COMPA_vect)
{
  if(is_pin_high(GSCLK_PORT, GSCLK_PIN))
  {
    //bring it low
    pin_low(GSCLK_PORT, GSCLK_PIN);
    //are we done?
    if(gsclk_counter == 4096)
    {
      //flash blank and reset counter
      pulse_pin(BLANK_PORT, BLANK_PIN);
      gsclk_counter = 0;
    }
  }
  else
  {
    //bring it high
    pin_high(GSCLK_PORT, GSCLK_PIN);
    //increment counter
    ++gsclk_counter;
  }
}

void configure_GSCLK_output(void)
{
  disable_GSCLK_output();

  //Set the OC1A and OC1B pins (Timer1 output pins A and B) to output mode
  //On Arduino UNO, etc, OC1A is Port B/Pin 1 and OC1B Port B/Pin 2
  
  //enable GSCLK as output
  GSCLK_DDR |= (1<<GSCLK_PIN);

  // Configure timer1 in CTC mode, for waveform generation, set to toggle OC1A, at /1 prescalar, interupt at CTC
  TCCR1A = (0<<COM1A1) | (1<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
  TCCR1B = (0<<ICNC1)  | (0<<ICES1)  | (0<<WGM13)  | (1<<WGM12)  | (0<<CS12)  | (1<<CS11) | (0<<CS10);

  //set the period
  half_period = 16; //that's 16 clock pulses.
  OCR1A = half_period;
  TCNT1 = 0; //get the timer rolling (not really necessary? defaults to 0. Just in case.)
}

void enable_GSCLK_output(void)
{
  pin_low(BLANK_PORT, BLANK_PIN);
  TIMSK1 |= (1<<OCIE1A);
}

void disable_GSCLK_output(void)
{
  TIMSK1 &= ~(1<<OCIE1A);
  pin_high(BLANK_PORT, BLANK_PIN);
  gsclk_counter = 0;
}