#ifndef HRSENSOR_H_
#define HRSENSOR_H_

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Arduino.h>
#include <BLE2902.h> 
#include <Wire.h>
#include <heartRate.h>
#include <MAX30105.h>
#include <spo2_algorithm.h>
#define HR_ARRAY_LENGTH 400
#define AUTOCORR_ARRAY_LENGTH HR_ARRAY_LENGTH/2
#define HEARTRATE_SERVICE_UUID "180D"
#define HEARTRATE_HEARTRATE_MEASUREMENT_UUID "2A37"
#define HEARTRATE_HEARTRATE_READ_UUID "783430ee-d3c5-4134-963d-4ff80878127c"

extern uint8_t  INITIAL_STATE;
extern uint8_t  STATE_ONE;
extern BLEServer *FYP_server;
class HRModule {
    public:
    HRModule();
    HRModule(byte ledBrightness, byte sampleAverage, byte ledMode, int sampleRate, int pulseWidth, int adcRange);
    void startReading();
    uint8_t getReadStateValue();
    uint8_t getCurrentHeartRate();

    private:
    byte ledBrightness; //Options: 0=Off to 255=50mA
    byte sampleAverage; //Options: 1, 2, 4, 8, 16, 32
    byte ledMode; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
    int sampleRate; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
    int pulseWidth; //Options: 69, 118, 215, 411
    int adcRange; //Options: 2048, 4096, 8192, 16384
    MAX30105 * particleSensor;

    float autocorr_transformed[AUTOCORR_ARRAY_LENGTH];
    uint32_t rawData[HR_ARRAY_LENGTH];
    uint8_t currentHeartRate[2];
    
    float Mean(uint32_t inputArray[]);
    void autoCorrelation (uint32_t inputArray[]);
    int getMaxIndex(float inputArray[],int begin, int end);
    unsigned long lastReadTime;
    int samplingRate;
    int N_Min;
    int N_Max;

    BLEService *heartrate_service;
    BLECharacteristic * heartrate_HRMeasurement;
    BLECharacteristic  * heartrate_HRRead;
    
    void BLESetup();
};

#endif