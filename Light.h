#ifndef __FX_H__
#define __FX_H__

#include "WProgram.h"
#include "Controller.h"

#define FULL_ON 32767
#define FULL_OFF 0

class Controller;

/// The FX class is an abstract class for handling lights and lighting effects.

//////////////////////////////////////////////////
/// The FX class provides the basic functionality for manipulating lights.
/// The class is the base class for Light, and for every special
/// effect in the library. The FX class does not provide a method
/// for storing references to other FX instances; this will have to be
/// added on an adhoc basis to derived classes. See some of the included
/// examples for suggestions.
///
/// All FX instances must be assigned to the Controller via Controller::addFX().
///
/// FX instances are stored in a singly-linked list in the Controller, which
/// ensures that the FX::setup() and FX::update() functions get called
/// at the right moments.
///
/// Implementing a deived class requires that you provide some method for
/// assigning one or more FX instances to be controlled. The base class provides
/// no such functionality, for the sake of space. (And because the Light class,
/// which is derived from FX, doesn't need it.)
//////////////////////////////////////////////////
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
    /// Returns the set current
    byte getDesiredCurrent(void);

  protected:
    bool _fading;
    byte _desired_current;
    int _dim;
    int _fade_target;
    float _fade_rate;
};

/// A class specifically for representing a single output on a TLC5941

//////////////////////////////
/// Each output channel on a TLC5941 that has lights attached requires one
/// and only one instance of a Light class. This class adjusts the current
/// output the TLC5941 for that channel using dot correction according to the
/// electrical specifications of what is actually attached.
///
/// All Lights must be assigned to a TLC5941 instance via TLC5941:addLight().
//////////////////////////////

#endif
