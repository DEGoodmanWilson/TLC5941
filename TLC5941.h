#ifndef __TLC5941_H__
#define __TLC5941_H__

#include "WProgram.h"
#include "Controller.h"
#include "Light.h"

class Controller;
class Light;

class TLC5941
{
  public:
    TLC5941(void);
    TLC5941(Controller *c);

    void setup(void);
    void update(void);

    void setDotCorrection(void);

    void addLight(int pos, Light *l);
    void addBoard(TLC5941 *next);

    void setMaxCurrent(byte current);
    void setCurrentResistor(int resistance);

  private:
    Light *_lights[16];
    //byte _max_current;
    TLC5941 *_nextBoard;
    Controller *_controller;
};

#endif
