#include "ECGModule.h"

ECGModule::ECGModule(){
    rawECG=0;
    BLESetup();
}

uint8_t ECGModule::getReadStateValue(){
    uint8_t * state = ECG_ECGRead->getData();
    return *state;
}

uint8_t ECGModule::getECGRaw(){
    return rawECG;
}

void ECGModule::startReading(int pin){
    if(millis() - lastNotify > 4){
        rawECG = analogRead(pin);
        Serial.println(rawECG);
        ECG_ECGMeasurement->setValue(rawECG);
        ECG_ECGMeasurement->notify();
        lastNotify= millis();
    }
}

void ECGModule::BLESetup(){
Serial.println("initializing heartrate Service");
    ECG_service = FYP_server->createService(ECG_SERVICE_UUID);
    ECG_ECGMeasurement = ECG_service->createCharacteristic(ECG_ECGMODULE_MEASUREMENT_UUID,
                                                        BLECharacteristic::PROPERTY_NOTIFY
                                                        );
    ECG_ECGMeasurement->addDescriptor(new BLE2902());

    ECG_ECGRead = new BLECharacteristic(ECG_ECGMODULE_READ_UUID,
                                                        BLECharacteristic::PROPERTY_WRITE | 
                                                        BLECharacteristic::PROPERTY_READ
                                                        );
    ECG_service->addCharacteristic(ECG_ECGRead);
    ECG_ECGRead->setValue(&INITIAL_STATE,1);
    ECG_service->start();
}