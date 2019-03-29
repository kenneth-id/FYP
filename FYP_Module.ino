#include "src/BLE/BLEModule.h"
#include "src/HRModule/HRModule.h"
#include "src/LED/LED.h"
#include "src/BIT_HW/BIT_HW.h"
#include "src/ECG/ECGModule.h"

//TODO: create event handler for server
//TODO: create event handler for characteristics 
//TODO: maybe add battery service?
//TODO: define for ECG

bool deviceConnected = false;
uint8_t link_loss_alert_level = 0;
uint8_t NO_ALERT =0;
int sensor_mode = 0;
// uint8_t currentHeartrate[2];

BLEService *thermometer_service=NULL;
BLEService *heartrate_service=NULL;  
BLEService *linkloss_service=NULL;

BLECharacteristic * heartrate_heartrate_measurement=NULL;
BLECharacteristic * thermometer_temperature_measurement=NULL;

HRModule * myHRModule = NULL;
ECGModule * myECGModule = NULL;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting FYP Module!");
  initLED();
  initRGB();
  initBIT_HW();
  boot_up();
  readBIT_HW();
  detect_sensor_module();
  delay(1000);
  //setRGB(HIGH, LOW, LOW, LOW);
  // BLESetUp();
  // myHRModule = new HRModule();
  myECGModule = new ECGModule();
}

void loop() {
  // if(deviceConnected){
    // currentHeartrate[0] = 0;
    // currentHeartrate[1] = 65;
    // heartrate_heartrate_measurement->setValue(currentHeartrate,2);
    // heartrate_heartrate_measurement->notify();
    
    myECGModule->startReading();
    Serial.println(myECGModule->getECGRaw());
    // myHRModule->startReading();
    // Serial.println(myHRModule->getCurrentHeartRate());
// 
  // }
  // if((link_loss_alert_level==2) && !deviceConnected){
  //   blink(2,500); //blink onboard LED
  // }
  // delay(4);
}
void boot_up() {
  setLED(HIGH, LOW, LOW);
  delay(300);
  setLED(HIGH, HIGH, LOW);
  delay(300);
  setLED(HIGH, HIGH, HIGH);
  delay(300);
  setLED(LOW, LOW, LOW);
  delay(300);
  setRGB(HIGH, LOW, HIGH, HIGH);  
  delay(300);
  setRGB(HIGH, HIGH, LOW, HIGH);  
  delay(300);
  setRGB(HIGH, HIGH, HIGH, LOW);  
  delay(300);
  setRGB(HIGH, LOW, LOW, LOW);  
  delay(300);
  setRGB(LOW, LOW, LOW, LOW);  
  delay(300);
}