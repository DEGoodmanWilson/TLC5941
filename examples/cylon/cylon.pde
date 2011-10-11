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
    lights[i].setCurrent(6);
    board1.addLight(i,&lights[i]);
  }
  for(int i = 8; i<16; ++i)
  {
    lights[i].setCurrent(2);
    board2.addLight(i,&lights[i]);
  }
  cylon.addLights(16,lights);

  cylon.setTimings(100, 200, 32);

  c.addBoard(&board1);
  c.addBoard(&board2);
  c.setup();

}

void loop()
{
  cur_time = millis();
  time_diff = cur_time - prev_time;
  cylon.update(time_diff);
  c.update();
  prev_time = cur_time;
}

