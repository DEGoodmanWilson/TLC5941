#include "Controller.h"
#include "ISR.h"

Controller::Controller(void)
{
  //set up necessary pins for output
  pinMode(BLANK,OUTPUT);
  pinMode(XLAT,OUTPUT);
  pinMode(SCLK,OUTPUT);
  pinMode(SIN,OUTPUT);
  pinMode(MODE,OUTPUT);
  pinMode(GSCLK,OUTPUT);

  _firstBoard = NULL;
}

void Controller::addBoard(TLC5941 *board)
{
  if(_firstBoard == NULL) //first board added!
  {
    Serial.println("Adding one board");
    _firstBoard = board;
  }
  else
  {
    Serial.println("Telling first board to add a second");
    _firstBoard->addBoard(board);
  }
}

void Controller::setup(void)
{
    //tell all Boards to setup!
    if(_firstBoard != NULL)
        _firstBoard->setup();

  //set up Dot Correction
  //first, enter DC mode
  pin_high(MODE_PORT, MODE_PIN);
  pin_high(BLANK_PORT, BLANK_PIN);

  //now, just output 96 1's! TODO
  //digitalWrite(SIN,HIGH);
  //for(int i = 0; i < 96; ++i)
  //{
  //  pulse_pin(SCLK_PORT,SCLK_PIN);
  //}
  //tell the boards to output their DC values, last board first
  Serial.println("Controller: Setting DC");
  _firstBoard->setDotCorrection();

  //now latch and exit DC mode
  pulse_pin(XLAT_PORT, XLAT_PIN); //is the latch not slow enough?
  pin_low(MODE_PORT, MODE_PIN);

  //because first GS cycle after setting DC requires an extra pulse of the ole' SCLK, just go ahead and do it now, whatever. We'll just set every light off for now.
  _firstBoard->update();
  pulse_pin(XLAT_PORT, XLAT_PIN);
  pin_low(BLANK_PORT, BLANK_PIN);
  pulse_pin(SCLK_PORT, SCLK_PIN); //the extra SCLK pulse
}

void Controller::update(void)
{
	//Here's what we need to do each loop:
	//  1. shift the GS data out
	//  2. pulse GSCLK 4096 (!!) times


  // 1. tell each board to shift out their GS data, last board first
    if(_firstBoard != NULL)
    {
        _firstBoard->update();
        pin_high(BLANK_PORT, BLANK_PIN);
        pulse_pin(XLAT_PORT, XLAT_PIN);
        pin_low(BLANK_PORT, BLANK_PIN);
    }
    else
    {
        pulse_pin(BLANK_PORT, BLANK_PIN); //resets the GSCLK counter
    }

  // 2. flash the GSCLK a whole lot!
  for(int i = 0; i < 4096; ++i)
  {
    pulse_pin(GSCLK_PORT,GSCLK_PIN);
  }
}

void Controller::MSBShiftOut(word w, byte length)
{
    for (word bit = 1<<(length-1); bit; bit >>= 1)
    {
        if (bit & w)
            SIN_PORT |= _BV(SIN_PIN);
        else
            SIN_PORT &= ~_BV(SIN_PIN);
        pulse_pin(SCLK_PORT,SCLK_PIN);
    }
}
