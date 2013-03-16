#include <Controller.h>
#include <Light.h>
#include <TLC5941.h>
#include <Traffic.h>

Controller c;
TLC5941 board(&c), board2(&c);
Light lights[16];
Traffic tc, tc2;

unsigned long cur_time = 0;
unsigned long prev_time = 0;
unsigned int time_diff;

void setup()
{
  //set up 16 LEDs, max 2mA current, off by default
  for(int i = 0; i <16; ++i)
  {
    lights[i].setCurrent(2);
    lights[i].dim(0);
    board.addLight(i,&lights[i]); //add to board
    tc.addLight(i, &lights[i]); //add to traffic controller class
  }
  
  //set up traffic controller  
  //Add aspects (light configurations) to animation, with timings in seconds
  tc.addState(ASPECT_NS_GREEN_PED_GREEN,10);
  tc.addState(ASPECT_NS_GREEN_PED_BLINK,4);
  tc.addState(ASPECT_NS_YELLOW_PED_BLINK,5);
  tc.addState(ASPECT_ALL_RED,1);
  tc.addState(ASPECT_EW_GREEN_PED_GREEN,10);
  tc.addState(ASPECT_EW_GREEN_PED_BLINK,4);
  tc.addState(ASPECT_EW_YELLOW_PED_BLINK,5);

  
  c.addBoard(&board);
  c.setup();
  prev_time = millis();
}

void loop()
{
  cur_time = millis();
  time_diff = cur_time - prev_time;
  //traffic controller class needs to know how much time passed since the last update
  // to ensure a consistent animation speed
  tc.update(time_diff);
  //update the controller; will automatically update each board assigned
  c.update();
  prev_time = cur_time;
}
