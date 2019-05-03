#ifndef BIT_VERIFICATION_H_
#define BIT_VERIFICATION_H_

#include "Arduino.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h> 

#define BIT_VERIFICATION_SERVICE_UUID "b63293a9-b78e-4811-8542-dd337f020a1e"
#define BIT_VERIFICATION_CHARACTERISTIC_UUID "503eb2ab-4aa4-46d1-b3c2-33663f10e126"
#define BIT1_HW       33
#define BIT2_HW       34

extern BLEServer *FYP_server;

enum sensorStates{NOSENSOR,HEARTRATE,TEMPERATURE,ECG};

class BitVerification{
    public:
    BitVerification();
    int getState();
    void updateState();

    private:
    int bit_1;
    int bit_2;
    BLEService * bit_verification_service;
    BLECharacteristic * bit_verification_characteristic;
    int state;

    void readBits();
};

#endif