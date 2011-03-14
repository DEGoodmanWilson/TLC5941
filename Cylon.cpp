#include "Cylon.h"

Cylon::Cylon(void)
{
//  for(int i = 0; i < 16; ++i)
 //   _lights[i] = NULL;
  _lights = NULL;
  _direction = 1;
  _cur_location = 0;
  _elapsed_time = 0;
  _fade_in_t = 100;
  _fade_out_t = 500;
  _dwell_t = 200;
}

void Cylon::addLights(byte howmany, Light *light_array)
{
  _lights = light_array;
  _num_lights = howmany;
}

void Cylon::setTimings(unsigned int fadein, unsigned int fadeout, float rate)
{
  _fade_in_t = fadein;
  _fade_out_t = fadeout;
  _dwell_t = (unsigned int)(1000./rate);
}

void Cylon::update(unsigned int time_diff)
{
  _elapsed_time += time_diff;
  if(_elapsed_time  > _dwell_t) //is it time to move on?
  {
    _elapsed_time = 0;
    //fade out current light;
    _lights[_cur_location].fadeto(0,_fade_out_t);
    //move to next light;
    _cur_location += _direction;
    //check for bounds
    if(_cur_location == _num_lights)
    {
      _cur_location = _num_lights-1;
      _direction = -1;
    }
    else if(_cur_location == -1)
    {
      _cur_location = 0;
      _direction = 1;
    }
    _lights[_cur_location].fadeto(32767,_fade_in_t);
  }

  for(int i = 0; i < _num_lights; ++i)
     _lights[i].update(time_diff);
}
