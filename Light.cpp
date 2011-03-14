#include "Light.h"

Light::Light(void)
{
    _dim = 0;
    _fading = false;
    _desired_current = 20; //default to 20ma
}

void Light::update(unsigned int time_diff)
{
    //update fade
    if(_fading)
    {
       float incr = time_diff * _fade_rate; //(float)(_fade_target-_dim)/(float)_fade_interval;
       //if(!incr) incr = 1; //just in case
       //_fade_last_time = cur_time;
       if(abs(_fade_target - _dim) <= abs(incr))
       {
         _fading = false;
         _dim = _fade_target;
       }
       else
       {
         _dim += incr;
       }
    }
}

void Light::dim(int ratio)
{
    if(ratio > 32767)
        _dim = 32767;
    else if(ratio < 0)
        _dim = 0;
    else
        _dim = ratio;
    _fading = false; //if this was called during a fade, override the fade now;
}

void Light::fadeto(int target, unsigned int time)
{

    if(target == _dim)
    {
      _fading = false;
      return;
    }
    _fade_target = target;
    if(_fade_target > 32767) _fade_target = 32767;
    if(_fade_target < 0) _fade_target = 0;
    _fade_rate = (float)(_fade_target-_dim)/(float)time;
    _fading = true;
}

int Light::getDim(void)
{
    return _dim;
}

void Light::setCurrent(byte desiredCurrent)
{
    _desired_current = desiredCurrent;
}

void Light::setBrightness(int nominalBrightness, byte nominalCurrent, int desiredBrightness)
{
    _desired_current = desiredBrightness*((float)nominalCurrent/(float)nominalBrightness);
}

byte Light::getDesiredCurrent(void)
{
    return _desired_current;
}
