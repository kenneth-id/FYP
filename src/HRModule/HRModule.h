#ifndef HRSENSOR_H_
#define HRSENSOR_H_

#include <Wire.h>
#include <heartRate.h>
#include <MAX30105.h>
#include <spo2_algorithm.h>
#define HR_ARRAY_LENGTH 400
#define AUTOCORR_ARRAY_LENGTH HR_ARRAY_LENGTH/2


class HRModule {
    public:
    HRModule();
    HRModule(byte ledBrightness, byte sampleAverage, byte ledMode, int sampleRate, int pulseWidth, int adcRange);
    void startReading();
    uint8_t getCurrentHeartRate();

    private:
    uint8_t currentHeartRate;

    float autocorr_transformed[AUTOCORR_ARRAY_LENGTH];
    uint32_t rawData[HR_ARRAY_LENGTH];

    MAX30105 * particleSensor;

    float Mean(uint32_t inputArray[]);
    void autoCorrelation (uint32_t inputArray[]);
    int getMaxIndex(float inputArray[],int begin, int end);

    int samplingRate;
    int N_Min;
    int N_Max;

    

};

#endif