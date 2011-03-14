#include "Traffic.h"

Traffic::Traffic()
{
  for(int i = 0; i < 16; ++i)
  {
    _lights[i] = NULL;
    _state_order[i] = 0;
    _state_timings[i] = 0;
  }
  _state = 0;
  _elapsed_time = 0;
  _blink_time = 00;
  _blinking = 0;
  _max_state = 0;
}

void Traffic::addLight(byte which, Light *light)
{
  _lights[which] = light;
}

void Traffic::addState(word aspect, byte duration)
{
  if(_max_state == 16) return;
  _state_timings[_max_state] = duration;
  _state_order[_max_state] = aspect;
  ++_max_state;
}

void Traffic::update(unsigned int time_diff)
{
  //blink light if necessary
  if(_blinking&(1<<0) || _blinking&(1<<2)) //is NS or EW blink bit set?
  {
    _blink_time += time_diff;
    if(_blink_time >= BLINK_TIME)
    {
      _blink_time = 0;
      if(_blinking&(1<<0))
        _lights[NS_PED_RED_LIGHT]->fadeto(_blinking&(1<<1)?0:32767, 100);
      if(_blinking&(1<<2))
        _lights[EW_PED_RED_LIGHT]->fadeto(_blinking&(1<<3)?0:32767, 100);
      _blinking ^= (1<<1 | 1<<3); //flip the blink state bits
    }
  }

  _elapsed_time += time_diff;

  //Is it time to change lights?
  if(_elapsed_time >= _state_timings[_state]*1000) // time to change state!
  {
    _elapsed_time = 0;
    _state = (_state+1)%_max_state;

    for(byte i = 0; i <16; ++i) //iterate through the 16bit state.
    {
      if(_lights[i] != NULL) //if there is a light attached to this output
      {
        _lights[i]->fadeto(_state_order[_state] & (1<<i)?32767:0, 100);
      }
    }

    //handle special case of blinking
    _blinking &= ~((1<<0) | (1<<2)); //clear NS and EW blinking flags
    if( (_state_order[_state] & NS_PED_BLINKING) == NS_PED_BLINKING )
    {
      _blinking |= 1<<0; //set ns blink flag
      _lights[NS_PED_GREEN_LIGHT]->dim(0); //supress off green light
    }
    else if( (_state_order[_state] & EW_PED_BLINKING) == EW_PED_BLINKING )
    {
      _blinking |= 1<<2;
      _lights[EW_PED_GREEN_LIGHT]->dim(0);
    }
  }

  for(int i = 0; i < 16; ++ i)
    if(_lights[i] != NULL)
    {
      _lights[i]->update(time_diff);
    }
}
