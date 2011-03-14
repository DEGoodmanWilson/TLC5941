#ifndef __CYLON_H__
#define __CYLON_H__

#include "WProgram.h"
#include "Light.h"

class Cylon
{
  public:
    Cylon(void);
    
    void update(unsigned int time_diff);
    void addLights(byte howmany, Light *light_array);
    //set time to fade in and out, and the rate in LEDs/second
    void setTimings(unsigned int fadein, unsigned int fadeout, float rate);
  private:
    byte _num_lights;
    int _direction;
    int _cur_location;
    unsigned int _elapsed_time;
    unsigned int _fade_in_t;
    unsigned int _fade_out_t;
    unsigned int _dwell_t;
    Light *_lights;
};

#endif
