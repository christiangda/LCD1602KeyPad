/* Arduino LCD1502KeyPad Library
   copyright Christian González <christiangda@gmail.com>, 2013
   this code is public domain, enjoy!
*/

#include <LCD1602KeyPad.h>   // include LCD library
#include <LiquidCrystal.h>

LCD1602KeyPad lcd;

void setup()
{
  lcd.begin();
  lcd.print( "LCD KeyPad 16x2" );
  //bottom left corner
  lcd.setCursor( 0, 1 );
  lcd.print( "Btn:" );
}

void loop()
{
  byte button;
  byte timestamp;
  boolean state;
  
  //get the latest button pressed
  button = lcd.readButtons();

  //blank the demo text line if a new button is pressed or released, ready for a new label to be written
  state = lcd.getButtonsState();
  if( state == RELEASED )
  {
    lcd.setCursor( 4, 1 );
    lcd.print( "          " );
  }

  //show text label for the button pressed
  switch( button )
  {
    case NONE:
    {
      break;
    }
    case RIGHT:
    {
      lcd.setCursor( 4, 1 );
      lcd.print( "RIGHT" );
      break;
    }
    case UP:
    {
      lcd.setCursor( 4, 1 );
      lcd.print( "UP" );
      break;
    }
    case DOWN:
    {
      lcd.setCursor( 4, 1 );
      lcd.print( "DOWN" );
      break;
    }
    case LEFT:
    {
      lcd.setCursor( 4, 1 );
      lcd.print( "LEFT" );
      break;
    }
    case SELECT:
    {
      lcd.setCursor( 4, 1 );
      lcd.print( "SELECT" );
      break;
    }
    default:
    {
      break;
    }
  }

  // print the number of seconds since reset (two digits only)
  timestamp = ( (millis() / 1000) % 100 );   //"% 100" is the remainder of a divide-by-100, which keeps the value as 0-99 even as the result goes over 100
  lcd.setCursor( 14, 1 );
  if( timestamp <= 9 )
  {
    lcd.print( " " );   //quick trick to right-justify this 2 digit value when it's a single digit
  }
  lcd.print( timestamp, DEC );
}