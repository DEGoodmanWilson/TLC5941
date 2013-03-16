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
  
  //just a quick test of the functionality; set up 16 LEDs
  //set them al to max brightness, and have them each dim slowly
  //to 0 over differing periods of time.
  for(int i = 0; i <16; ++i)
  {
    lights[i].setCurrent(2); //set to 2mA current
    lights[i].dim(32767); //make full brightness on
    lights[i].fadeto(0,100*i); //fade to zero brightness over 100*i milliseconds
    board.addLight(i,&lights[i]);
  }

  c.addBoard(&board);
  c.setup();
}

void loop()
{

  c.update();
}

