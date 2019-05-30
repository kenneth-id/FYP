#include "src/BLE/BLEServer.h"
#include "src/HRModule/HRModule.h"
#include "src/TempModule/TempModule.h"
#include "src/ECGModule/ECGModule.h"
#include "src/BitVerification/BitVerification.h"
#include "src/LED/LED.h"
#include "src/RGB/RGB.h"

// Define analog pin
#define ANALOG1     25
#define ANALOG2     26

bool deviceConnected = false;
BitVerification * bitVerification= NULL;
BLEServer * FYP_server=NULL;

HRModule * myHRModule = NULL;
TempModule * myTempModule= NULL;
ECGModule * myECGModule= NULL;

LED * LEDLeft =NULL;
LED * LEDCenter = NULL;
LED * LEDRight = NULL;
RGB * rgbLED= NULL;

uint8_t INITIAL_STATE=0;
uint8_t STATE_ONE=1;
  
void setup() {
  Serial.begin(115200);
  Serial.println("Starting FYP Module!");
  Serial.println("initialize LEDs");
  LEDLeft = new LED(12,300,300,false);
  LEDCenter = new LED(13,300,300,false);
  LEDRight = new LED(14,300,300,false);
  rgbLED= new RGB(0,0,0,300,300,false);
  Serial.println("initialize Analog pins as INPUT");
  pinMode(ANALOG1, INPUT);
  pinMode(ANALOG2, INPUT);
  BLESetUp();
  Wire.begin();
  myHRModule = new HRModule();
  myTempModule= new TempModule();
  myECGModule= new ECGModule();
  bitVerification = new BitVerification();
}

void loop() {
  bitVerification->updateState();
  LEDLeft->updateLED();
  LEDCenter->updateLED();
  LEDRight->updateLED();
  rgbLED->updateRGB();
  if(deviceConnected){
    //if no sensor module is connected
    if(bitVerification->getState()==0){
      LEDLeft->setLEDState(LOW);
      LEDCenter->setLEDState(LOW);
      LEDRight->setLEDState(LOW);
    }
    //if HR sensor module is connected
    if(bitVerification->getState()==1){
      LEDLeft->setLEDState(HIGH);
      LEDCenter->setLEDState(LOW);
      LEDRight->setLEDState(LOW);
      if(myHRModule->getReadStateValue()==1){
        myHRModule->startReading();
      }
    }
    //if temperature sensor module is connected
    if(bitVerification->getState()==2){
      LEDLeft->setLEDState(LOW);
      LEDCenter->setLEDState(HIGH);
      LEDRight->setLEDState(LOW);
      if(myTempModule->getReadStateValue()==1){
        myTempModule->startReading();
      }
    }
    //if ECG sensor module is connected
    if(bitVerification->getState()==3){
      LEDLeft->setLEDState(LOW);
      LEDCenter->setLEDState(LOW);
      LEDRight->setLEDState(HIGH);
      if(myECGModule->getReadStateValue()==1){
        myECGModule->startReading(ANALOG1);
      }
    }
  }
  // delay(4);
}
