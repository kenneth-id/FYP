#include "src/BLE/BLEServer.h"
#include "src/HRModule/HRModule.h"

//TODO: create event handler for server
//TODO: create event handler for characteristics 
//TODO: maybe add battery service?
//TODO: define for ECG

bool deviceConnected = false;
// uint8_t currentHeartrate[2];
BLEServer * FYP_server=NULL;
HRModule * myHRModule = NULL;

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
  BLESetUp();
  myHRModule = new HRModule();
}

void loop() {
  // if(deviceConnected){
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
    digitalWrite(14,HIGH);
    // currentHeartrate[0] = 0;
    // currentHeartrate[1] = 65;
    // heartrate_heartrate_measurement->setValue(currentHeartrate,2);
    // heartrate_heartrate_measurement->notify();

    // myHRModule->startReading();
    // Serial.println(myHRModule->getCurrentHeartRate());

  // }
  // if((link_loss_alert_level==2) && !deviceConnected){
  //   blink(2,500); //blink onboard LED
  // }
  // delay(4);
}
