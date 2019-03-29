#ifndef BLESERVER_H_
#define BLESERVER_H_

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Arduino.h>
#include <BLE2902.h> //for client characteristic configuration descriptor

extern uint8_t link_loss_alert_level;
extern bool deviceConnected;
extern uint8_t NO_ALERT;
extern BLEService *thermometer_service;
extern BLEService *heartrate_service;  
extern BLEService *linkloss_service;
extern BLECharacteristic * heartrate_heartrate_measurement;
extern BLECharacteristic * thermometer_temperature_measurement; 
void BLESetUp();

#endif