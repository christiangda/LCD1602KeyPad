/* 
 LCD1602KeyPad.h - Arduino library to control LCD 16x2 with KeyPad Shield
 Copyright 2013 Christian González <christiangda@gmail.com>
*/

#ifndef LCD1602KeyPad_h
#define LCD1602KeyPad_h

//External Library
#include <Arduino.h>
#include "LiquidCrystal.h"

/*--------------------------------------------------------------------------------------
  Defines
--------------------------------------------------------------------------------------*/
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
#define PIN_BUTTON_ADC  A0 // A0 is the button ADC input
#define PIN_LCD_b4      4  //
#define PIN_LCD_b5      5  //
#define PIN_LCD_b6      6  //
#define PIN_LCD_b7      7  //
#define PIN_LCD_RS      8  //
#define PIN_LCD_E       9  //
#define PIN_LCD_K       10 // D10 controls LCD backlight

// LCD Dimensions
#define LCD_COL    16
#define LCD_ROW    2
#define CHAR_SIZE  LCD_5x10DOTS // from LiquidCrystal.h

// ADC readings expected for the 5 buttons on the ADC input
#define BTN_RIGHT_ADC   0
#define BTN_UP_ADC      145
#define BTN_DOWN_ADC    329
#define BTN_LEFT_ADC    507
#define BTN_SELECT_ADC  742
#define BTN_NONE_ADC    1023
#define BTN_ADC_GAP     20

//return values
#define NONE    0
#define RIGHT   1
#define UP      2
#define DOWN    3
#define LEFT    4
#define SELECT  5

// Controlling BackLihgt
#define OFF  false
#define ON   true

#define PRESSED   true
#define RELEASED  false

//
class LCD1602KeyPad: public LiquidCrystal
{
	public:
		LCD1602KeyPad();		// Constructor
		~LCD1602KeyPad();		// Destructor
		void begin();
		void setBackLight(boolean);
		void setBackLightFlash(unsigned int);
		void setButtonsState(boolean);
		boolean getButtonsState();
		uint8_t readButtons();
	
	private:
		boolean _btn_state;
		uint8_t _btn_last;
};

#endif