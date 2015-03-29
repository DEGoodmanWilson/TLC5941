#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "Arduino.h"
#include "TLC5941.h"

class TLC5941;

/*
   The following def's show which Arduino pins this library expects to be
   used with each input to the TLC5941. If any of these are changed, please
   update the def's for individual ports and pins below as well.
*/
#define GSCLK 2
#define BLANK 3
#define XLAT 4
#define SCLK 5
#define SIN 6
#define MODE 7

#define GSCLK_PIN PIND2
#define GSCLK_DDR DDRD
#define GSCLK_PORT PORTD

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

/// The Controller class handles all low-level hardware stuff.

//////////////////////////////////////////////////
/// Most interaction with this library will be through the Controller class.
/// The class should be instantiated once and only once. The results of
/// multiple instantiations are undefined. Minimally, you should call
/// Controller::setup() in the setup() function, and Controller::update()
/// in the update() function. To actually do anything, however, you will need
/// to instantiate at least one TLC5941 class, and pass it to the Controller
/// instance via Controller::addBoard().
//////////////////////////////////////////////////
class Controller
{
  public:
    Controller(void);
    /// Assigns a TLC5941 to be controlled.
    
    //////////////////////////////////////////////////
    /// %TLC5941 chips can be daisychained together in a (logically) indefinte
    /// quantity. For each %TLC5941 in the chain, a TLC5941 class should be
    /// instantiated to represent it. Controller::addBoard is used to add
    /// each %TLC5941 chip to the controller. Call Controller::addBoard in order
    /// from the first %TLC5941 in the chain to the last.
    //////////////////////////////////////////////////
    void addBoard(TLC5941 *board);

    /// Called in the sketch's setup()

    //////////////////////////////////////////////////
    /// Does initialization and set up. For each
    /// assigned board, it calls that board's setup()
    /// function as well.
    //////////////////////////////////////////////////
    void setup(void);

    /// Update the controller's state; call once in loop()

    //////////////////////////////////////////////////
    /// Makes sure that every board assigned to the
    /// controller is updated each time through the
    /// sketch loop. Call inside of loop().
    //////////////////////////////////////////////////
    void update(void);

    /// Internal function for shifting data to each board
    void MSBShiftOut(word w, byte length);

  private:
    TLC5941 *_firstBoard;
};


#endif
