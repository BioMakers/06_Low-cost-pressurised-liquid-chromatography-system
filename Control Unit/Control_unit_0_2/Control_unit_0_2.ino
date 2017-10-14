//Include Wire library for I2C communication
#include <Wire.h>

//Include Grove RGB LCD library
#include "rgb_lcd.h"

//Addresses for I2C devices
byte pump1Address = 9;
byte pump2Address = 10;
byte fracAddress = 11;

//Key inputs for analog buttons
#define UP       0
#define DOWN     1
#define LEFT     2
#define RIGHT    3
#define SELECT   4
#define NOKEY    5
int buttonPin = A3;
int button;

//Start an instance of the rgb_lcd class called lcd
rgb_lcd lcd;

//Variables for cursor position
int cursorX = 0;
int cursorY = 0;

//Variables to monitor menu progression
int state = 2;
int cont = 0;

void setup()
{
  //Start serial communication
  Serial.begin(9600);
  
  //Start I2C communication
  Wire.begin();
  
  //Setup the LCD - 16 characters per line, 2 lines - background white
  lcd.begin(16,2);
  lcd.setRGB(255,255,255);
  lcd.noBlink();  
}

void loop()
{
 //Title screen
  while (state == 0)
  {
    //Show the title screen
    lcd.setCursor(2,0);
    lcd.print("Open-source");
    lcd.setCursor(4,1);
    lcd.print("FPLC 1.0");
    delay(2000);
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Biomaker");
    lcd.setCursor(1,1);
    lcd.print("Challenge 2017");
    delay(2000);
    lcd.clear();
    state = 1;
  }
  
  //Check connection to I2C devices 
  while(state ==1)
  {
    lcd.setCursor(1,0);
    lcd.print("Connecting....");
    delay(1000);
    
    //Check if pump 1 is connected and display results on LCD
    if(checkI2Cdevice(pump1Address))
    {
      lcd.clear();
      lcd.print("Pump 1 connected");
      delay(1000);
    }
    else
    {
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cannot connect");
      lcd.setCursor(5,1);
      lcd.print("Pump 1");
      delay(1000);    
    }
    
    //Check if pump 2 is connected and display results on LCD
    if(checkI2Cdevice(pump2Address))
    {
      lcd.clear();
      lcd.print("Pump 2 connected");
      delay(1000);
    }
    else
    {
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cannot connect");
      lcd.setCursor(5,1);
      lcd.print("Pump 2");
      delay(1000);    
    }
  
    //Check if fraction collector is connected and display results on LCD
    if(checkI2Cdevice(fracAddress))
    {
      lcd.clear();
      lcd.print(" Frac connected ");
      delay(1000);
    }
    else
    {
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cannot connect");
      lcd.setCursor(6,1);
      lcd.print("Frac");
      delay(1000);    
    }
  
  //Display a menu that allows user to either continue or try to reconnect devices
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Continue");
    lcd.setCursor(4,1);
    lcd.print("Reconnect");
    lcd.setCursor(0,0);
    lcd.blink();
    cursorX = 0;
    cursorY = 0;
    
    //Process input from buttons to allow menu selection
    while(true)
    {
      //Read the input buttons and move cursor according to the choice made (up or down only) 
      button = ReadButton();
      
      //Process input from DOWN button and move cursor depending on the current location of the cursor
      if(button == DOWN)
      {
        if(cursorY == 0)
        {
         cursorY += 1;
         lcd.setCursor(0,cursorY);
         delay(200);
        }
        else if (cursorY == 1)
        {
         cursorY -= 1;
         lcd.setCursor(0,cursorY);
         delay(200);         
        }
      }
      
      //Process input from the UP button and move cursor depending on the current location of the cursor
      if(button == UP)
      {
        if(cursorY ==1)
        {
          cursorY -= 1;
          lcd.setCursor(0,cursorY);
          delay(200);
        }
        else if(cursorY == 0)
        {
          cursorY += 1;
          lcd.setCursor(0,cursorY);
          delay(200);
        }
      }
      
      //Process input from the select button
      if(button == SELECT)
      {
        if(cursorY == 0)
        {
          state = 2;
          delay(200);
          break;
        }
        else if (cursorY == 1)
        {
          lcd.clear();
          delay(200);
          break;
        }
      }
    }
  }

//
  while(state == 2)
  {
    lcd.clear();
  }  
  
}

//Function to check if I2C device responds - derived from I2Cscanner by Nick Gammon 
//http://www.gammon.com.au/forum/?id=10896
bool checkI2Cdevice(byte deviceaddress)
{
  byte error;
  
  //Check if the device at the indicated address responds and then return true if connected
  Wire.beginTransmission(deviceaddress);
  error = Wire.endTransmission();
  
  if(error == 0)
  {
    return true; 
  }
  else
  {
    return false;
  }
}


//Function to read button input from one analog pin defined in buttonPin
//Uses five buttons attached to different resistor values to get a different analog
//output depending on the button pressed.
int ReadButton()
{
  //Read the analog button
  int keyvalue = analogRead(buttonPin);
  
  //Check value and assign key pressed (calibrated values) - if you change the resistors, these values will change
  if(keyvalue <= 300)
  {
    return NOKEY;
  }
  if(keyvalue <= 599)
  {
    return SELECT;
  }
  if(keyvalue <= 749)
  {
    return RIGHT;
  }
  if(keyvalue <= 949)
  {
    return LEFT;
  }
   if(keyvalue <= 989)
  {
    return DOWN;
  } 
  if(keyvalue <= 1023)
  {
    return UP;    
  } 
}