#ifndef __TRAFFIC_H__
#define __TRAFFIC_H__

#include "Arduino.h"
#include "Light.h"


#define BLINK_TIME 300

#define NS_GREEN_LIGHT 0
#define NS_YELLOW_LIGHT 1
#define NS_RED_LIGHT 2
#define NS_TURN_GREEN_LIGHT 3
#define NS_TURN_YELLOW_LIGHT 4
#define NS_TURN_RED_LIGHT 5
#define NS_PED_GREEN_LIGHT 6
#define NS_PED_RED_LIGHT 7
#define EW_GREEN_LIGHT 8
#define EW_YELLOW_LIGHT 9
#define EW_RED_LIGHT 10
#define EW_TURN_GREEN_LIGHT 11
#define EW_TURN_YELLOW_LIGHT 12
#define EW_TURN_RED_LIGHT 13
#define EW_PED_GREEN_LIGHT 14
#define EW_PED_RED_LIGHT 15

#define NS_GREEN 1<<0
#define NS_YELLOW 1<<1
#define NS_RED 1<<2
#define NS_TURN_GREEN 1<<3
#define NS_TURN_YELLOW 1<<4
#define NS_TURN_RED 1<<5
#define NS_PED_GREEN 1<<6
#define NS_PED_RED 1<<7
#define EW_GREEN 1<<8
#define EW_YELLOW 1<<9
#define EW_RED 1<<10
#define EW_TURN_GREEN 1<<11
#define EW_TURN_YELLOW 1<<12
#define EW_TURN_RED 1<<13
#define EW_PED_GREEN 1<<14
#define EW_PED_RED 1<<15

#define ASPECT_NS_ALL_RED		NS_RED|NS_TURN_RED|NS_PED_RED
#define ASPECT_EW_ALL_RED		EW_RED|EW_TURN_RED|EW_PED_RED
#define ASPECT_ALL_RED			ASPECT_NS_ALL_RED|ASPECT_EW_ALL_RED

#define ASPECT_NS_GREEN			NS_GREEN|NS_TURN_RED|NS_PED_RED|ASPECT_EW_ALL_RED
#define ASPECT_NS_YELLOW		NS_YELLOW|NS_TUR_RED|NS_PED_RED|ASPECT_EW_ALL_RED
#define ASPECT_NS_TURN_GREEN		NS_RED|NS_TURN_GREEN|NS_PED_RED|ASPECT_EW_ALL_RED
#define ASPECT_NS_TURN_YELLOW		NS_RED|NS_TURN_YELLOW|NS_PED_RED|ASPECT_EW_ALL_RED
#define ASPECT_NS_GREEN_PED_GREEN	NS_GREEN|NS_TURN_RED|NS_PED_GREEN|ASPECT_EW_ALL_RED
#define ASPECT_NS_GREEN_PED_BLINK	NS_GREEN|NS_TURN_RED|NS_PED_GREEN|NS_PED_RED|ASPECT_EW_ALL_RED
#define ASPECT_NS_YELLOW_PED_BLINK	NS_YELLOW|NS_TURN_RED|NS_PED_GREEN|NS_PED_RED|ASPECT_EW_ALL_RED

#define ASPECT_EW_GREEN                 EW_GREEN|EW_TURN_RED|EW_PED_RED|ASPECT_NS_ALL_RED
#define ASPECT_EW_YELLOW                EW_YELLOW|EW_TUR_RED|EW_PED_RED|ASPECT_NS_ALL_RED
#define ASPECT_EW_TURN_GREEN            EW_RED|EW_TURN_GREEN|EW_PED_RED|ASPECT_NS_ALL_RED
#define ASPECT_EW_TURN_YELLOW           EW_RED|EW_TURN_YELLOW|EW_PED_RED|ASPECT_NS_ALL_RED
#define ASPECT_EW_GREEN_PED_GREEN       EW_GREEN|EW_TURN_RED|EW_PED_GREEN|ASPECT_NS_ALL_RED
#define ASPECT_EW_GREEN_PED_BLINK       EW_GREEN|EW_TURN_RED|EW_PED_GREEN|EW_PED_RED|ASPECT_NS_ALL_RED
#define ASPECT_EW_YELLOW_PED_BLINK      EW_YELLOW|EW_TURN_RED|EW_PED_GREEN|EW_PED_RED|ASPECT_NS_ALL_RED

#define NS_PED_BLINKING 192
#define EW_PED_BLINKING 49152


//////////////////////////////
/// Manages a simple traffic light with three aspects in two directions.
/// Assumes that the timing will be the same for both directions.
//////////////////////////////
class Traffic
{
  public:
    Traffic(void);
    void addLight(byte which, Light *light);
    void addState(word aspect, byte duration);

    void update(unsigned int time_diff);

  private:
    byte _state;
    byte _state_timings[16]; //these need to be dynamic!
    word _state_order[16]; //really.
    Light *_lights[16];
    unsigned int _elapsed_time;
    unsigned int _blink_time;
    byte _blinking;
    byte _max_state;
};

#endif
