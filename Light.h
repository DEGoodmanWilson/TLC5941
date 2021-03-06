#ifndef __FX_H__
#define __FX_H__

#include "Arduino.h"
#include "Controller.h"

#define FULL_ON 32767
#define FULL_OFF 0

class Controller;

/// The Light class is an abstract class for handling lights and lighting effects.

//////////////////////////////////////////////////
/// The Light class provides the basic functionality for manipulating individual
/// output channels on each TLC5941 chip.
///
/// Each output channel on a TLC5941 that has lights attached requires one
/// and only one instance of a Light class. This class adjusts the current
/// output the TLC5941 for that channel using dot correction according to the
/// electrical specifications of what is actually attached.
///
/// All Lights must be assigned to a TLC5941 instance via TLC5941:addLight().
//////////////////////////////

class Light
{
  public:
    Light(void);

    /// Update the effect. Called by Controller::update()

    //////////////////////////////////////////////////
    /// Here is where the magic happens. This will be called
    /// periodically by Controller. On these occasions, a derived
    /// class will update its state, e.g. for animation.
    /// Does nothing; must be implemented.
    //////////////////////////////////////////////////
    void update(unsigned int time_diff);

    /// Set brightness to range [0,1], where 0 is full off and 1 is full on

    //////////////////////////////////////////////////
    /// The dim level is used to control the brightness of an effect.
    /// If the derived class looks at _dim to determine how bright it should
    /// be there is no reason to re-implement these methods
    //////////////////////////////////////////////////
    void dim(int ratio);
    /// Returns the current brightness
    int getDim(void);
    /// Slowly fades brightness from current value to target over time
    void fadeto(int target, unsigned int time);

    /// Set the output current for this channel in mA; if not called, default is 20mA.
    void setCurrent(byte desiredCurrent);
    /// Set the output current by requesting a set brightness
    void setBrightness(int nominalBrightness, byte nominalCurrent, int desiredBrightness);
    void off(void) {dim(0);}
    /// Returns the set current
    byte getDesiredCurrent(void);

  protected:
    bool _fading;
    byte _desired_current;
    int _dim;
    int _fade_target;
    float _fade_rate;
};
#endif
