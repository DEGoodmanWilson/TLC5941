#include <Controller.h>
#include <Light.h>
#include <TLC5941.h>
#include <Cylon.h>

Controller c;
TLC5941 board1(&c), board2(&c);
Light lights[32];
Cylon cylon;

unsigned long cur_time = 0;
unsigned long prev_time = 0;
unsigned int time_diff;
void setup()
{
  for(int i = 0; i <8; ++i)
  {
    //Set up each of 8 lights on one board to limit current to 6mA
    lights[i].setCurrent(6);
    board1.addLight(i,&lights[i]);
  }
  for(int i = 8; i<16; ++i)
  {
    //And on a second daisy-chained board, set up 8 lights to 2mA
    lights[i].setCurrent(2);
    board2.addLight(i,&lights[i]);
  }
  
  //Add the 16 lights to the Cylon special effects class
  cylon.addLights(16,lights);

  //set the timings for scan speed and decay
  cylon.setTimings(100, 200, 32);

  //add the two boards to the controller
  c.addBoard(&board1);
  c.addBoard(&board2);
  c.setup();

}

void loop()
{
  cur_time = millis();
  time_diff = cur_time - prev_time;
  //cylon class needs to know how much time passed since the last update
  // to ensure a consistent animation speed
  cylon.update(time_diff);
  //update the controller; will automatically update each board assigned
  c.update();
  prev_time = cur_time;
}

