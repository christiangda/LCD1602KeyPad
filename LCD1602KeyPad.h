/*
 LCD1602KeyPad.h - Arduino library to control LCD 16x2 with KeyPad Shield
 Copyright 2013 Christian González <christiangda@gmail.com>
*/
// Reference: https://luckyresistor.me/knowledge/avoid-preprocessor-macros/
#pragma once

//External Library
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include "LiquidCrystal.h"

enum class ButtonKey { NONE, RIGHT, LEFT, UP, DOWN, SELECT };
enum class ButtonState { IDLE, PRESSED, HOLD, RELEASED };

//
class LCD1602KeyPad: public LiquidCrystal
{
	public:
		LCD1602KeyPad();
		~LCD1602KeyPad();
		void begin();
		void setBackLight(bool);
		void setBackLightFlash(unsigned long);
		void setButtonsState(ButtonState);
		ButtonState getButtonsState();
		ButtonKey readButtons();

	private:
		ButtonState _btnState;
		ButtonKey _btnLast;
};
