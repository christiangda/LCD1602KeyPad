/*
 LCD1602KeyPad.h - Arduino library to control LCD 16x2 with KeyPad Shield
 Copyright 2013 Christian González (christiangda@gmail.com)
*/

// External Library
#include <Arduino.h>
#include "LiquidCrystal.h"

// Local Headers
#include "LCD1602KeyPad.h"

/*
 CLASS LCD1602KeyPad
*/
LCD1602KeyPad::LCD1602KeyPad() : LiquidCrystal(PIN_LCD_RS, PIN_LCD_E, PIN_LCD_b4, PIN_LCD_b5, PIN_LCD_b6, PIN_LCD_b7)
{
	//button adc input
	pinMode( PIN_BUTTON_ADC, INPUT );
	digitalWrite( PIN_BUTTON_ADC, LOW );

	//lcd backlight control
	pinMode( PIN_LCD_K, OUTPUT );
	digitalWrite( PIN_LCD_K, HIGH );
}

// Destructor
LCD1602KeyPad::~LCD1602KeyPad()
{
	//do something here? (free(), delete()?)
}

// Initialization
void LCD1602KeyPad::begin()
{
	//set up the LCD number of columns, rows  and character size
	LiquidCrystal::begin( LCD_COL, LCD_ROW, CHAR_SIZE);

	//Initialice the cursor
	LiquidCrystal::setCursor( 0, 0 );

	//init privated
	_btn_state = ButtonState::RELEASED;
	_btn_last = ButtonKey::NONE;
}

//
void LCD1602KeyPad::setBackLight(bool state)
{
	digitalWrite( PIN_LCD_K, state );
}

//
void LCD1602KeyPad::setBackLightFlash(unsigned long time)
{
	setBackLight(false);
	delay(time);
	setBackLight(true);
}

//
void LCD1602KeyPad::setButtonsState(ButtonState state)
{
	_btn_state = state;
}

//
ButtonState LCD1602KeyPad::getButtonsState()
{
	return _btn_state;
}

// Detect the button pressed and return the value
ButtonKey LCD1602KeyPad::readButtons()
{
   unsigned int v; //0-1023 values
   ButtonKey b = ButtonKey::NONE;   // default return

   //read the button ADC pin voltage
   v = analogRead( PIN_BUTTON_ADC );

   //sense if the voltage falls within valid voltage windows
   if( v < ( BTN_RIGHT_ADC + BTN_ADC_GAP ) )
   {
      b = ButtonKey::RIGHT;
   }
   else if( v <= ( BTN_UP_ADC + BTN_ADC_GAP ) )
   {
      b = ButtonKey::UP;
   }
   else if( v <= ( BTN_DOWN_ADC + BTN_ADC_GAP ) )
   {
      b = ButtonKey::DOWN;
   }
   else if( v <= ( BTN_LEFT_ADC + BTN_ADC_GAP ) )
   {
      b = ButtonKey::LEFT;
   }
   else if( v <= ( BTN_SELECT_ADC + BTN_ADC_GAP ) )
   {
      b = ButtonKey::SELECT;
   }

   //handle button flags for just pressed and just released events
   if( ( _btn_last == ButtonKey::NONE ) && ( b != ButtonKey::NONE ) )
   {
      _btn_state  = ButtonState::PRESSED;
   }
   if( ( _btn_last != ButtonKey::NONE ) && ( b == ButtonKey::NONE ) )
   {
      _btn_state  = ButtonState::RELEASED;
   }

   //save the latest button state
   _btn_last = b;

   return( b );
}
