#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Button.h> // https://github.com/JChristensen/Button
#include "bmp.h"


#define BLACK 0
#define WHITE 1

#define WIDTH 400
#define HEIGHT 240

#define SHARP_SCK  14
#define SHARP_MOSI 13
#define SHARP_SS   15

#define ADC_BAT 39
#define CRG_STAT 36

#define ABUT 33
#define BBUT 32
#define UBUT 19
#define DBUT 23
#define LBUT 22
#define RBUT 18
#define CBUT 21

Adafruit_SharpMem display(SHARP_SCK, SHARP_MOSI, SHARP_SS, 400, 240);

Button buttonA(ABUT, false, false, 5); //pin, pullup, invert, debounce
Button buttonB(BBUT, false, false, 5);
Button buttonUp(UBUT, true, true, 5); // turn on pullups for joystick only
Button buttonDown(DBUT, true, true, 5);
Button buttonLeft(LBUT, true, true, 5);
Button buttonRight(RBUT, true, true, 5);
Button buttonC(CBUT, true, true, 5);

unsigned long fpsCounter = 0;
float fps = 0;


void setup() {
  pinMode(0, OUTPUT); // don't change, -10µA???

  display.begin();
  display.clearDisplay();
  display.setRotation(0); //Tetris?

  Serial.begin(1000000);
  Serial.setTimeout(500);
  Serial.setRxBufferSize(12200);
  
  pinMode(ABUT, INPUT);
  pinMode(BBUT, INPUT);
  pinMode(UBUT, INPUT_PULLUP);
  pinMode(DBUT, INPUT_PULLUP);
  pinMode(LBUT, INPUT_PULLUP);
  pinMode(RBUT, INPUT_PULLUP);
  pinMode(CBUT, INPUT_PULLUP);

  pinMode(CRG_STAT, INPUT);
  pinMode(ADC_BAT, INPUT);
  
  
  display.clearDisplay();   // clears the screen and buffer
  
  display.drawBitmap(0, 0, bmp_swap, 400, 240, BLACK);
  display.refresh();
  //delay(500);
}

void loop() {
  fps = 1000/float(millis()-fpsCounter);
  fpsCounter = millis();

  if(buttonA.wasPressed() or buttonA.pressedFor(300)){
    Serial.print("1");
  }
  if(buttonB.wasPressed() or buttonB.pressedFor(300)){
    Serial.print("2");
  }
  if(buttonUp.wasPressed() or buttonUp.pressedFor(300)){
    Serial.print("3");
  }
  if(buttonDown.wasPressed() or buttonDown.pressedFor(300)){
    Serial.print("4");
  }
  if(buttonLeft.wasPressed() or buttonLeft.pressedFor(300)){
    Serial.print("5");
  }
  if(buttonRight.wasPressed() or buttonRight.pressedFor(300)){
    Serial.print("6");
  }

  
  if (Serial.available() > 0){
    byte command = Serial.read();
    if(command >= '0' && command <= '8'){
      if(command == '0'){
        display.fillScreen(BLACK);
        //display.drawBitmap(0, 0, bmp_swap, 400, 240, BLACK);
        unsigned int bytesReceived = Serial.readBytes(bmp_swap,12000);      
        //display.clearDisplay();
  
        /*
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(0, 20);
        display.print(char(command));
        display.print("-");
        display.println(bytesReceived);
        */
        display.drawBitmap(0, 0, bmp_swap, 400, 240, WHITE);
        display.refresh();
      }
    }
  }
  
  

  buttonA.read();
  buttonB.read();
  buttonUp.read();
  buttonDown.read();
  buttonLeft.read();
  buttonRight.read();
  buttonC.read();

  //delay(10);

}
