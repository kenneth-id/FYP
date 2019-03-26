#ifndef TEMPMODULE_H_
#define TEMPMODULE_H_
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Arduino.h>
#include <BLE2902.h> 
#include <Protocentral_MAX30205.h>

#define THERMOMETER_SERVICE_UUID "1809"
#define THERMOMETER_TEMPERATURE_MEASUREMENT_UUID "2A1C"

extern BLEServer *FYP_server;
class TempModule {
    public:
    TempModule();
    float getCurrentTemperature();
    void startReading();
    void setBLECharacteristic();
    private:
    MAX30205 * tempSensor;
    BLEService * thermometer_service;
    BLECharacteristic * thermometer_temperature_measurement;
    float currentTemperature;
    unsigned long lastReadTime;

    void BLESetUp();
};
#endif