#include "BLEModule.h"

//TODO: create event handler for server
//TODO: create event handler for characteristics 
//TODO: maybe add battery service?
//TODO: define for ECG

bool deviceConnected = false;
uint8_t link_loss_alert_level = 0;
uint8_t NO_ALERT =0;  
void setup() {
  Serial.begin(115200);
  Serial.println("Starting FYP Module!");
  pinMode(2,OUTPUT); //for on board LED 
  BLESetUp();
}

void loop() {
  if(deviceConnected){
    digitalWrite(2,LOW);
  }
  if((link_loss_alert_level==2) && !deviceConnected){
    digitalWrite(2,HIGH);
    delay(500);
    digitalWrite(2,LOW);
    delay(500);
  }
}
