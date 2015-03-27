#ifndef __FIRE_H__
#define __FIRE_H__

#include "Arduino.h"
#include "Light.h"

///////////
/// Simulates a fire glow. Can use one or two LEDs
/// The random nature is very processor intensive, and so doesn't work well with
/// more than a couple of output channels. Could be updated to use a psuedo-random
/// lookup table, which would be much faster.
///////////

class Fire
{
  public:
    Fire(void);

    void addLights(byte homany, Light *light_array);

    void update();

  private:
    Light *_lights;
    byte _num_lights;
    unsigned int _prev_time;
    unsigned long _elapsed_time;
};

#endif
