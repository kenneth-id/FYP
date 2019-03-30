#include "src/BLE/BLEServer.h"
#include "src/HRModule/HRModule.h"
#include "src/TempModule/TempModule.h"
#include "src/ECGModule/ECGModule.h"

// Define analog pin
#define ANALOG1     25
#define ANALOG2     26
//TODO: Add bit checking for currently connected sensor
//TODO: Add button controls
//TODO: Create better algorithm for TempModule read and sending BLE


bool deviceConnected = false;
BLEServer * FYP_server=NULL;
HRModule * myHRModule = NULL;
TempModule * myTempModule= NULL;
ECGModule * myECGModule= NULL;
uint8_t INITIAL_STATE=0;
uint8_t STATE_ONE=1;

void blink(uint8_t pin, uint_fast32_t interval){
    digitalWrite(pin,HIGH);
    delay(interval);
    digitalWrite(pin,LOW);
    delay(interval);
}  
void setup() {
  Serial.begin(115200);
  Serial.println("Starting FYP Module!");
  pinMode(12,OUTPUT); //for on board LED 
  pinMode(13,OUTPUT); //for on board LED
  pinMode(14,OUTPUT); //for on board LED
  Serial.println("initialize Analog pins as INPUT");
  pinMode(ANALOG1, INPUT);
  pinMode(ANALOG2, INPUT);
  BLESetUp();
  Wire.begin();
  myHRModule = new HRModule();
  myTempModule= new TempModule();
  myECGModule= new ECGModule();
}

void loop() {
  if(deviceConnected){
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
    digitalWrite(14,HIGH);
    // uncomment to test HRModule
    if(myHRModule->getReadStateValue()==1){
      myHRModule->startReading();
    }
    if(myTempModule->getReadStateValue()==1){
      myTempModule->startReading();
    }
    if(myECGModule->getReadStateValue()==1){
      myECGModule->startReading(ANALOG1);
    }
  }
  // delay(4);
}
