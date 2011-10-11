#include <Controller.h>
#include <Light.h>
#include <TLC5941.h>

Controller c;
TLC5941 board(&c);
Light lights[16];

unsigned long m;
unsigned long prev;

void setup()
{
  Serial.begin(9600);
  delay(500);
  Serial.println("Beginning setup");

  for(int i = 0; i <16; ++i)
  {
    lights[i].setCurrent(2);
    lights[i].dim(32767);
    lights[i].fadeto(0,100*i);
    board.addLight(i,&lights[i]);
  }

  c.addBoard(&board);
  c.setup();
}

void loop()
{

  c.update();
}

