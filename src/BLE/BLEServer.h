#ifndef BLESERVER_H_
#define BLESERVER_H_

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Arduino.h>
#include <BLE2902.h> //for client characteristic configuration descriptor
#include "../RGB/RGB.h"
extern RGB * rgbLED;
extern bool deviceConnected;
extern BLEServer *FYP_server;
void BLESetUp();


#endif