#include <Controller.h>
#include <Light.h>
#include <TLC5941.h>
#include <Fire.h>

Controller c;
TLC5941 board(&c);
Light lights[2];
Fire fire, fire2;

unsigned long m;

void setup()
{
  for(int i = 0; i <2; ++i)
  {
    lights[i].setCurrent(3);
    lights[i].off();
    board.addLight(i,&lights[i]);
  }
  fire.addLights(2,lights);

  c.addBoard(&board);
  c.setup();
}

void loop()
{
  m = millis();
  fire.update(m);
  c.update();
}

