#include "Fire.h"

Fire::Fire(void)
{
  _lights = NULL;
  _num_lights = 0;
  _elapsed_time = 0;
  randomSeed(analogRead(4));
}

void Fire::addLights(byte howmany, Light *light_array)
{
  _lights = light_array;
  _num_lights = howmany;
}

void Fire::update(unsigned int time_diff)
{
  int permute;
  int permutetime;
  int i;
  
  _elapsed_time += time_diff;
  //do we change the glow? allow a random amount of time to pass
  if(_elapsed_time >= random(200,3001))
  {
    _elapsed_time = 0;
    //first, we take a random brightness, and a random time period.
    //now, for each light, use a random variation on these values:
    for(i = 0; i < _num_lights; ++i)
    {
      permute = random(5000,25000);
      permutetime = 300;//random(50,500);
      _lights[i].fadeto(permute,permutetime);
    }
  }
  for(i = 0; i < _num_lights; ++i)
    _lights[i].update(time_diff);
}
