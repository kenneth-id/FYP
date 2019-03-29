#include "ECGModule.h"

ECGModule::ECGModule(){
    rawECG=0;
    BLESetup();
}

uint8_t ECGModule::getReadStateValue(){
    uint8_t * state = ecg_ECGRead->getData();
    return *state;
}

uint8_t ECGModule::getECGRaw(){
    //Serial.println("inside getECGRaw function");
    return rawECG;
}

void ECGModule::initAnalogPin(){
    Serial.println("initialize Analog Pin as INPUT");
    pinMode(ANALOG1, INPUT);
    pinMode(ANALOG2, INPUT);
}

void ECGModule::startReading(){
    //Serial.println("inside startReading function");
    rawECG = analogRead(ANALOG1);
    Serial.println(rawECG);
    delay(1);
}

void ECGModule::BLESetup(){

}