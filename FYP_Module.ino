#include "src/BLE/BLEModule.h"
#include "src/HRModule/HRModule.h"

//TODO: create event handler for server
//TODO: create event handler for characteristics 
//TODO: maybe add battery service?
//TODO: define for ECG

bool deviceConnected = false;
uint8_t link_loss_alert_level = 0;
uint8_t NO_ALERT =0;

// uint8_t currentHeartrate[2];

BLEService *thermometer_service=NULL;
BLEService *heartrate_service=NULL;  
BLEService *linkloss_service=NULL;

BLECharacteristic * heartrate_heartrate_measurement=NULL;
BLECharacteristic * thermometer_temperature_measurement=NULL;

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
  pinMode(2,OUTPUT); //for on board LED 
  // BLESetUp();
  myHRModule = new HRModule();
}

void loop() {
  // if(deviceConnected){
    digitalWrite(2,LOW);
    // currentHeartrate[0] = 0;
    // currentHeartrate[1] = 65;
    // heartrate_heartrate_measurement->setValue(currentHeartrate,2);
    // heartrate_heartrate_measurement->notify();

    myHRModule->startReading();
    Serial.println(myHRModule->getCurrentHeartRate());

  // }
  // if((link_loss_alert_level==2) && !deviceConnected){
  //   blink(2,500); //blink onboard LED
  // }
  // delay(4);
}
