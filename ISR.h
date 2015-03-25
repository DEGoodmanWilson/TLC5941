#include <avr/io.h>

/*
   The following def's show which Arduino pins this library expects to be
   used with each input to the TLC5941. If any of these are changed, please
   update the def's for individual ports and pins below as well.
*/
#define GSCLK 9
#define BLANK 3
#define XLAT 4
#define SCLK 5
#define SIN 6
#define MODE 7

#define GSCLK_PIN PINB1
#define GSCLK_DDR DDRB
#define GSCLK_PORT PORTB

#define BLANK_PIN PIND3
#define BLANK_DDR DDRD
#define BLANK_PORT PORTD

#define XLAT_PIN PIND4
#define XLAT_DDR DDRD
#define XLAT_PORT PORTD

#define SCLK_PIN PIND5
#define SCLK_DDR DDRD
#define SCLK_PORT PORTD

#define SIN_PIN PIND6
#define SIN_DDR DDRD
#define SIN_PORT PORTD

#define MODE_PIN PIND7
#define MODE_PORT PORTD

#define pulse_pin(port, pin)   port |= _BV(pin); port &= ~_BV(pin)
#define pin_high(port, pin) port |= _BV(pin)
#define pin_low(port, pin) port &= ~_BV(pin)
#define is_pin_high(port, pin) (port & (1 << pin))

void configure_GSCLK_output(void);
void enable_GSCLK_output(void);
void disable_GSCLK_output(void);