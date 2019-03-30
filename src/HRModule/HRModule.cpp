#include "HRModule.h"

HRModule::HRModule():autocorr_transformed(),rawData(){
    Serial.println("inside HRSensor constructor");
    //Use default I2C port, 400kHz speed
    particleSensor = new MAX30105();
    ledBrightness = 0x1F; //Options: 0=Off to 255=50mA
    sampleAverage = 8; //Options: 1, 2, 4, 8, 16, 32
    ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
    sampleRate = 400; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
    pulseWidth = 411; //Options: 69, 118, 215, 411
    adcRange = 4096; //Options: 2048, 4096, 8192, 16384
    
    samplingRate= sampleRate/sampleAverage;
    N_Min=(int)samplingRate*0.5;
    N_Max=(int)samplingRate*1.2;
    currentHeartRate[0]=0;
    currentHeartRate[1]=0;
    lastReadTime=0.0;
    BLESetup();
}

HRModule::HRModule(byte ledBrightness, byte sampleAverage, byte ledMode, int sampleRate, int pulseWidth, int adcRange){
    Serial.println("inside HRSensor constructor");
    particleSensor = new MAX30105();
   
    this->ledBrightness = ledBrightness; //Options: 0=Off to 255=50mA
    this->sampleAverage = sampleAverage; //Options: 1, 2, 4, 8, 16, 32
    this->ledMode = ledMode; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
    this->sampleRate = sampleRate; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
    this->pulseWidth = pulseWidth; //Options: 69, 118, 215, 411
    this->adcRange = adcRange; //Options: 2048, 4096, 8192, 16384
    
    samplingRate= sampleRate/sampleAverage;
    N_Min=(int)samplingRate*0.5;
    N_Max=(int)samplingRate*1.2;
    currentHeartRate[0]=0;
    currentHeartRate[1]=0;
    lastReadTime=0.0;
    BLESetup();
}
uint8_t HRModule::getReadStateValue(){
    uint8_t * state =heartrate_HRRead->getData();
    return *state;
}
void HRModule::startReading(){
    //Use default I2C port, 400kHz speed
    if (!particleSensor->begin(Wire, I2C_SPEED_FAST)) {
        Serial.println("MAX30105 was not found. Please check wiring/power. ");
    }
    particleSensor->setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);
    Serial.println("inside startReading function");
    if(particleSensor->getIR()>50000){
        Serial.println("Start sensor reading!");
        for(int i=0; i< HR_ARRAY_LENGTH;i++){
            rawData[i]=particleSensor->getIR();
            // Serial.println(rawData[i]);
        }
        autoCorrelation(rawData);
        Serial.print("N_Min= ");
        Serial.println(N_Min);
        Serial.print("N_Max= ");
        Serial.println(N_Max);
        int peakIndex = getMaxIndex(autocorr_transformed,N_Min,N_Max);
        Serial.print("peakIndex= ");
        Serial.println(peakIndex);
        int HBR= 60*samplingRate/(peakIndex);
        Serial.print("HBR= ");
        Serial.println(HBR);
        currentHeartRate[0]=0;
        currentHeartRate[1]=HBR;
        heartrate_HRMeasurement->setValue(currentHeartRate,2);
        heartrate_HRMeasurement->notify();
        heartrate_HRRead->setValue(&INITIAL_STATE,1);
    }
    else{
        Serial.println("Finger not detected.");
    }
}
uint8_t HRModule::getCurrentHeartRate(){
    Serial.println("inside getCurrentHeartRate function");
    return currentHeartRate[1];
}

//https://www.alanzucconi.com/2016/06/06/autocorrelation-function/
void HRModule::autoCorrelation (uint32_t inputArray[]){
    float mean = Mean(inputArray);
    for (int t = 0; t < AUTOCORR_ARRAY_LENGTH; t ++){ // 200 is hardcoded, plz change
        float Numerator = 0.0; // Numerator
        float Denominator = 0.0; // Denominator
        for (int i = 0; i < HR_ARRAY_LENGTH; i ++){
            float xim = inputArray[i] - mean;
            Numerator += xim * (inputArray[(i + t) % HR_ARRAY_LENGTH] - mean);
            Denominator += xim * xim;
        }
    autocorr_transformed[t] = Numerator / Denominator;
    }
}

float HRModule::Mean(uint32_t inputArray[]){
    int arrayLength= sizeof(inputArray)/sizeof(uint32_t);
    float sum =0.0;
    for(int i=0; i< arrayLength;i++){
        sum+= inputArray[i];
    }
    float mean = sum/arrayLength;
    return mean;
}

int HRModule::getMaxIndex(float inputArray[],int begin, int end){
    float tempMax= inputArray[begin];
    int maxIndex=begin;
    for(int i=begin; i<end; i++){
        // Serial.println(inputArray[i]);
        if(inputArray[i]>tempMax){
            tempMax= inputArray[i];
            maxIndex=i;
        }
    }
    return maxIndex;
}
void HRModule::BLESetup(){
    Serial.println("initializing heartrate Service");
    heartrate_service = FYP_server->createService(HEARTRATE_SERVICE_UUID);
    heartrate_HRMeasurement = heartrate_service->createCharacteristic(HEARTRATE_HEARTRATE_MEASUREMENT_UUID,
                                                        BLECharacteristic::PROPERTY_NOTIFY
                                                        );
    heartrate_HRMeasurement->addDescriptor(new BLE2902());

    heartrate_HRRead = new BLECharacteristic(HEARTRATE_HEARTRATE_READ_UUID,
                                                        BLECharacteristic::PROPERTY_WRITE | 
                                                        BLECharacteristic::PROPERTY_READ
                                                        );
    heartrate_service->addCharacteristic(heartrate_HRRead);
    heartrate_HRRead->setValue(&INITIAL_STATE,1);
    heartrate_service->start();
}
