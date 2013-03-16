#ifndef __TLC5941_H__
#define __TLC5941_H__

#include "Arduino.h"
#include "Controller.h"
#include "Light.h"

class Controller;
class Light;

/// The TLC5941 class is representation of a particular TLC5941 chip.

//////////////////////////////////////////////////
/// The TLC5941 class exposes the low-level functionality of each
/// chip in a daisy-chain---it will need to be instantiated once for
/// each chip in use.
///
/// All TLC5941 instances must be assigned to the Controller via Controller::addBoard().
///
//////////////////////////////////////////////////

class TLC5941
{
  public:
    TLC5941(void);
    TLC5941(Controller *c);

    void setup(void); //called once in the setup() function
    void update(void); //called repeatedly

    void setDotCorrection(void); //commit LED current limiting factors

    void addLight(int pos, Light *l); //must be called for each output channel actually in use
    void addBoard(TLC5941 *next); //called by Controller::addBoard() to construct the linked list

    void setMaxCurrent(byte current); //set the maximum allowable current globally for entire board
    void setCurrentResistor(int resistance); //if a current-setting resistor is used, you must register the value here. Require for current limitation calculations

  private:
    Light *_lights[16];
    //byte _max_current;
    TLC5941 *_nextBoard;
    Controller *_controller;
};

#endif
