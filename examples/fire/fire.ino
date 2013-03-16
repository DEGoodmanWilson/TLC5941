#include <Controller.h>
#include <Light.h>
#include <TLC5941.h>
#include <Fire.h>

Controller c;
TLC5941 board(&c);
Light lights[2];
Fire fire;

unsigned long cur_time = 0;
unsigned long prev_time = 0;
unsigned int time_diff;

void setup()
{
  
  //set up two LEDs, max 3mA current, and turn each off
  for(int i = 0; i <2; ++i)
  {
    lights[i].setCurrent(3);
    lights[i].off();
    board.addLight(i,&lights[i]);
  }
  //add the lights to the fire FX class
  fire.addLights(2,lights);

  c.addBoard(&board);
  c.setup();
}

void loop()
{
  cur_time = millis();
  time_diff = cur_time - prev_time;
  //fire's update function requires a time difference since last call
  fire.update(time_diff);
  //update the controller
  c.update();
  prev_time = cur_time;
}

