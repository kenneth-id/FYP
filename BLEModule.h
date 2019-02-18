#ifndef BLEMODULE_H_
#define BLEMODULE_H_

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Arduino.h>
#include <BLE2902.h> //for client characteristic configuration descriptor

extern uint8_t link_loss_alert_level;
extern bool deviceConnected;
extern uint8_t NO_ALERT;
void BLESetUp();

#endif