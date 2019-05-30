#ifndef TEMPMODULE_H_
#define TEMPMODULE_H_
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Arduino.h>
#include <BLE2902.h> 
#include <Protocentral_MAX30205.h>

#define THERMOMETER_SERVICE_UUID "1809"
#define THERMOMETER_TEMPERATURE_MEASUREMENT_UUID "2A1F"
#define THERMOMETER_TEMP_READ_UUID "36c9de24-7501-4292-baf0-7c1fa79f5787"

extern uint8_t  INITIAL_STATE;
extern uint8_t  STATE_ONE;
extern BLEServer *FYP_server;
class TempModule {
    public:
    TempModule();
    float getCurrentTemperature();
    void startReading();
    uint8_t getReadStateValue();
    private:
    MAX30205 * tempSensor;
    BLEService * thermometer_service;
    BLECharacteristic * thermometer_temperature_measurement;
    BLECharacteristic  * thermometer_tempRead;
    float currentTemperature;
    void BLESetUp();
};
#endif