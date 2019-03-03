#ifndef TEMPMODULE_H_
#define TEMPMODULE_H_
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Arduino.h>
#include <BLE2902.h> 
#include <Protocentral_MAX30205.h>

class TempModule {
    public:
    TempModule();
    float getCurrentTemperature();
    void startReading();
    bool setBLECharacteristic();
    private:
    MAX30205 * tempSensor;
    BLEService * thermometer_service;
    BLECharacteristic * thermometer_temperature_measurement;
    float currentTemperature;

    void BLESetUp();
};
#endif