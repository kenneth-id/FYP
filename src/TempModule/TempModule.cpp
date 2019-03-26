#include "TempModule.h"
TempModule::TempModule(){
    tempSensor = new MAX30205();
    BLESetUp();
    currentTemperature=0.0;
    lastReadTime=0.0;
}
float TempModule::getCurrentTemperature(){
    return currentTemperature;
}
void TempModule::startReading(){

}
void TempModule::setBLECharacteristic(){
    
}

void TempModule::BLESetUp(){
    thermometer_service = FYP_server->createService(THERMOMETER_SERVICE_UUID);
    thermometer_temperature_measurement = thermometer_service->createCharacteristic(THERMOMETER_TEMPERATURE_MEASUREMENT_UUID,
        BLECharacteristic::PROPERTY_INDICATE
    );
    thermometer_temperature_measurement->addDescriptor(new BLE2902());
    thermometer_service->start();
}