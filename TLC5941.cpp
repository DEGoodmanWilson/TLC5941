#include "TLC5941.h"

TLC5941::TLC5941(void)
{
	_controller = NULL;
	_nextBoard = NULL;
	for(int i = 0; i < 16; ++i)
		_lights[i] = NULL;
}

TLC5941::TLC5941(Controller *c)
{
	_controller = c;
	_nextBoard = NULL;
	for(int i = 0; i < 16; ++i)
		_lights[i] = NULL;
}

void TLC5941::setup(void)
{
	//TODO!! anything need to be done here? Don't think so.
	if(_nextBoard != NULL)
		_nextBoard->setup();
}

void TLC5941::update(void)
{
  //update last board first, so allow the next board (if there is one) to do its thing first.
  if(_nextBoard != NULL)
    _nextBoard->update();

  //now, let's get down to business. for each light 0-15, we determine a 12-bit grayscale value, and pump it out SIN
  //brightness[0,1] = GSn/4095
  //therefore
  //GSn = brightness*4095
  word GS;
  for(int n = 15; n >= 0; --n)
  {
    if(_lights[n] == NULL)
      GS = 0;
    else {
      GS = word(((float)_lights[n]->getDim()/32767.0) * 4095);
    }
    _controller->MSBShiftOut(GS,12);
  }
}

void TLC5941::setDotCorrection(void)
{
	//The calling class is responsible for entering and leaving DC mode!!
	//each channel can output at most 80mA.
	//Each channel defaults to requesting 20mA, but this can be overridden by the user. We override this value in software by setting the dot correction.

	//We shift out last board first. So, tell the next board to go ahead, then we'll do out thing.
        Serial.println("TLC5941: Setting DC");
	if(_nextBoard != NULL)
		_nextBoard->setDotCorrection();
	
	//Shift out the Dot correction factors for this board's channels.
	// since IOUTn = Imax * (DCn/63)
	// and we need to calculate DCn given IOUTn, Imax:
	// DCn = 63*(IOUTn/Imax)
        byte DC;
	for(int n = 15; n >=0 ; --n)
	{
		DC = 0;
		if(_lights[n] != NULL)
                {
		  DC = byte(63.0*((float)_lights[n]->getDesiredCurrent() / 80.0));
                  if(DC == 0 && _lights[n]->getDesiredCurrent() > 0)
                    DC = 1;
                }
		//Now, we have to output this value aas a 6-bit word! eww!
                Serial.print("TLC5941: DC ");
                Serial.print(n);
                Serial.print(" ");
                Serial.println((int)DC);
		_controller->MSBShiftOut(DC,6);
	}
	Serial.println("TLC5941: Done setting DC");
}

void TLC5941::addLight(int pos, Light *l)
{
	if(pos > 15) pos = 15;
	else if(pos < 0) pos = 0;
	_lights[pos] = l;
}

void TLC5941::addBoard(TLC5941 *next)
{
  Serial.println("TLC5941: Adding board");
	if(_nextBoard == NULL)
		_nextBoard = next;
	else _nextBoard->addBoard(next);
}