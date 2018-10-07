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
 Pins used by LCD & Keypad Shield:

    A0:  Buttons, analog input from voltage ladder
    D4:  LCD bit 4
    D5:  LCD bit 5
    D6:  LCD bit 6
    D7:  LCD bit 7
    D8:  LCD RS
    D9:  LCD E
    D10: LCD K Backlight (high = on, also has pullup high so default is on)

  ADC voltages for the 5 buttons on analog input pin A0:

    RIGHT:  0.00V :   0 @ 8bit ;   0 @ 10 bit
    UP:     0.71V :  36 @ 8bit ; 145 @ 10 bit
    DOWN:   1.61V :  82 @ 8bit ; 329 @ 10 bit
    LEFT:   2.47V : 126 @ 8bit ; 507 @ 10 bit
    SELECT: 3.62V : 185 @ 8bit ; 741 @ 10 bit
*/

// Pins in use
const byte PIN_BUTTON_ADC = A0; // A0 is the button ADC input
const byte PIN_LCD_b4 = 4;
const byte PIN_LCD_b5 = 5;
const byte PIN_LCD_b6 = 6;
const byte PIN_LCD_b7 = 7;
const byte PIN_LCD_RS = 8;
const byte PIN_LCD_E = 9;
const byte PIN_LCD_K = 10; // D10 controls LCD backlight

// ADC readings expected for the 5 buttons on the ADC input
const unsigned int BTN_RIGHT_ADC = 0;
const unsigned int BTN_UP_ADC = 145;
const unsigned int BTN_DOWN_ADC = 329;
const unsigned int BTN_LEFT_ADC = 507;
const unsigned int BTN_SELECT_ADC = 742;
const unsigned int BTN_NONE_ADC = 1023;
const unsigned int BTN_ADC_GAP = 20;

// LCD Dimensions
const byte LCD_COL = 16;
const byte LCD_ROW = 2;
const byte CHAR_SIZE = LCD_5x10DOTS; // from LiquidCrystal.h

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
	_btnState = ButtonState::RELEASED;
	_btnLast = ButtonKey::NONE;
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
	_btnState = state;
}

//
ButtonState LCD1602KeyPad::getButtonsState()
{
	return _btnState;
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
   if( ( _btnLast == ButtonKey::NONE ) && ( b != ButtonKey::NONE ) )
   {
      _btnState  = ButtonState::PRESSED;
   }
   if( ( _btnLast != ButtonKey::NONE ) && ( b == ButtonKey::NONE ) )
   {
      _btnState  = ButtonState::RELEASED;
   }

   //save the latest button state
   _btnLast = b;

   return( b );
}
