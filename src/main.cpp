#include <Arduino.h>

#include "../include/Free_Fonts.h" //include free fonts library from https://github.com/Seeed-Studio/Seeed_Arduino_LCD/blob/master/examples/320x240/Free_Font_Demo/Free_Fonts.h
#include "TFT_eSPI.h"

#include "AHT20.h"

TFT_eSPI tft;

AHT20 AHT; // Temperature and humidity sensor

void setup()
{
  // put your setup code here, to run once:

  // set up screen
  tft.begin();
  tft.setRotation(2);

  AHT.begin();
}

void loop()
{
  // put your main code here, to run repeatedly:

  TFT_eSprite spr = TFT_eSprite(&tft); //Initializing buffer

  spr.createSprite(TFT_WIDTH, TFT_HEIGHT); // Create buffer (portrait)

  spr.fillSprite(TFT_GREENYELLOW); //Fill background

  spr.fillRect(0, 0, 240, 30, TFT_WHITE); // Header portion
  spr.setFreeFont(FMB12);
  //  spr.setTextSize(1);
  spr.setTextColor(TFT_BLACK);
  spr.drawString("Grove AHT20", 5, 6);

  float humi, temp;

  int ret = AHT.getSensor(&humi, &temp);
  if (ret)
  { // GET DATA OK
  }
  else
  { // GET DATA FAIL
    humi = 0.99;
    temp = 99;
  }

  //Setting temperature
  spr.setFreeFont(FMB18);
  spr.setTextDatum(MC_DATUM);
  spr.drawString("Temperature", 120, 85);
  spr.setFreeFont(FMB24);
  spr.setTextDatum(MR_DATUM);
  spr.drawFloat(temp, 1, 160, 120);
  spr.setTextDatum(ML_DATUM);
  spr.drawString("C", 160, 120);

  //Setting humidity
  spr.setFreeFont(FMB18);
  spr.setTextDatum(MC_DATUM);
  spr.drawString("Humidity", 120, 205);
  spr.setFreeFont(FMB24);
  spr.setTextDatum(MR_DATUM);
  spr.drawNumber(humi * 100, 100, 240); //Display humidity values
  spr.setTextDatum(ML_DATUM);
  spr.drawString("%RH", 100, 240);

  spr.pushSprite(0, 0); //Push to LCD

  spr.deleteSprite();
}
