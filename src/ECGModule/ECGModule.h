#ifndef ECGMODULE_H_
#define ECGMODULE_H_

#include "Arduino.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h> 

#define ECG_SERVICE_UUID "886d9be6-3f47-4190-96f3-7a3cc4522a69"
#define ECG_ECGMODULE_MEASUREMENT_UUID "1be13a4f-d8f1-431e-94a9-c40c26e15086"
#define ECG_ECGMODULE_READ_UUID "78a49d7b-5a00-47fc-a851-f2c71249e9af"

extern uint8_t INITIAL_STATE;
extern uint8_t STATE_ONE;
extern BLEServer *FYP_server;
class ECGModule {
    public:
    ECGModule();
    void startReading(int pin);
    uint8_t getReadStateValue();
    
    uint8_t getECGRaw();

    private:
    BLEService *ECG_service;
    BLECharacteristic *ECG_ECGMeasurement;
    BLECharacteristic *ECG_ECGRead;
    uint16_t rawECG;
    void BLESetup();
};

#endif