#include "HRSensor.h"

HRSensor::HRSensor(){
    //Use default I2C port, 400kHz speed
    particleSensor = new MAX30105();
    if (!particleSensor->begin(Wire, I2C_SPEED_FAST)) {
        Serial.println("MAX30105 was not found. Please check wiring/power. ");
        while (1);
    }
    byte ledBrightness = 0x1F; //Options: 0=Off to 255=50mA
    byte sampleAverage = 8; //Options: 1, 2, 4, 8, 16, 32
    byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
    int sampleRate = 400; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
    int pulseWidth = 411; //Options: 69, 118, 215, 411
    int adcRange = 4096; //Options: 2048, 4096, 8192, 16384
    particleSensor->setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);
    samplingRate= sampleRate/sampleAverage;
    N_Min=(int)samplingRate*0.5;
    N_Max=(int)samplingRate*1.2;
    Serial.println("inside HRSensor constructor");
}

HRSensor::HRSensor(byte ledBrightness, byte sampleAverage, byte ledMode, int sampleRate, int pulseWidth, int adcRange){
    //Use default I2C port, 400kHz speed
    if (!particleSensor->begin(Wire, I2C_SPEED_FAST)) {
        Serial.println("MAX30105 was not found. Please check wiring/power. ");
        while (1);
    }
    particleSensor->setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);
    samplingRate= sampleRate/sampleAverage;
}
void HRSensor::startReading(){
    if(particleSensor->getIR()>50000){
        Serial.println("Start sensor reading!");
        for(int i=0; i< HR_ARRAY_LENGTH;i++){
            rawData[i]=particleSensor->getIR();
        }
    }
    else{
        Serial.println("Finger not detected.");
    }

    autoCorrelation(rawData);
    int peakIndex = getMaxIndex(autocorr_transformed,N_Min,N_Max);
    int HBR= 60*samplingRate/(N_Min+peakIndex);
    currentHeartRate=HBR;
}
uint8_t HRSensor::getCurrentHeartRate(){
    return currentHeartRate;
}

//https://www.alanzucconi.com/2016/06/06/autocorrelation-function/
void HRSensor::autoCorrelation (uint32_t inputArray[]){
    float mean = Mean(inputArray);
    int inputLength= sizeof(inputArray)/sizeof(uint32_t);
    int autocorrLength= sizeof(autocorr_transformed)/sizeof(float);
    for (int t = 0; t < autocorrLength; t ++){ // 200 is hardcoded, plz change
        float Numerator = 0.0; // Numerator
        float Denominator = 0.0; // Denominator
        for (int i = 0; i < inputLength; i ++){
            float xim = inputArray[i] - mean;
            Numerator += xim * (inputArray[(i + t) % inputLength] - mean);
            Denominator += xim * xim;
        }
    autocorr_transformed[t] = Numerator / Denominator;
    }
}

float HRSensor::Mean(uint32_t inputArray[]){
    int arrayLength= sizeof(inputArray)/sizeof(uint32_t);
    float sum =0.0;
    for(int i=0; i< arrayLength;i++){
        sum+= inputArray[i];
    }
    float mean = sum/arrayLength;
    return mean;
}

int HRSensor::getMaxIndex(float inputArray[],int begin, int end){
    float tempMax= 0.0;
    int maxIndex=0;
    for(int i=begin; i<end; i++){
        if(inputArray[i]>tempMax){
            tempMax= inputArray[i];
            maxIndex=i;
        }
    }
    return maxIndex;
}

void HRSensor::debug(){
    Serial.println("Inside debug function");
}