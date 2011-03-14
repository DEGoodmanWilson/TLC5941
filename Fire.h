#ifndef __FIRE_H__
#define __FIRE_H__

#include "WProgram.h"
#include "Light.h"

/// Simulates a fire glow. Can use one or two LEDs

//////////////////////////////
/// Simulates a fire glow
//////////////////////////////
class Fire
{
  public:
    Fire(void);

    void addLights(byte homany, Light *light_array);

    void update(unsigned int time_diff);

  private:
    Light *_lights;
    byte _num_lights;
    unsigned long _elapsed_time;
};

#endif
