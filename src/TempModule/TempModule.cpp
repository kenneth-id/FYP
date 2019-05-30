#include "TempModule.h"
TempModule::TempModule(){
    tempSensor = new MAX30205();
    BLESetUp();
    currentTemperature=0.0;
}
float TempModule::getCurrentTemperature(){
    return currentTemperature;
}
uint8_t TempModule::getReadStateValue(){
    uint8_t * state =thermometer_tempRead->getData();
    return *state;
}

void TempModule::startReading(){
    tempSensor->begin();
    currentTemperature = tempSensor->getTemperature();
    uint16_t toSend= static_cast<uint16_t>(10 * currentTemperature); //should be int16_t
    Serial.println(toSend);
    
    // uint8_t toSend[5] = {0,0,0,0,0};
    // uint8_t asInt = *((uint8_t*)&currentTemperature);
    // union {
    // float a;
    // char *floatToConvert = ( char* ) & currentTemperature;
    // toSend[1]=floatToConvert[0];
    // toSend[2]=floatToConvert[1];
    // toSend[3]=floatToConvert[2];
    // toSend[4]=floatToConvert[3];
    
    // char *returnFloat = ( char* ) & retVal;
    // } thing;
    // thing.a=currentTemperature;
    // for (int i=0; i<4; ++i) 
    // toSend[i+1]= (asInt >> 8 * i) & 0xFF;

    Serial.println(currentTemperature);
    
    // memcpy(&toSend[1],&currentTemperature,sizeof(float));
    // *((float*)toSend[1]) = currentTemperature;
    // toSend[1]= currentTemperature;
    // toSend[2]=currentTemperature >> 8;
    // toSend[3]=currentTemperature;
    // toSend[4]=currentTemperature;
    // toSend[5]=currentTemperature;
    // toSend[1]=reinterpret_cast<unsigned char *>(&currentTemperature);
    thermometer_temperature_measurement->setValue(toSend);
    thermometer_temperature_measurement->indicate();
    // thermometer_tempRead->setValue(&INITIAL_STATE,1);
    
}

void TempModule::BLESetUp(){
    Serial.println("initializing thermometer Service");
    thermometer_service = FYP_server->createService(THERMOMETER_SERVICE_UUID);
    thermometer_temperature_measurement = thermometer_service->createCharacteristic(THERMOMETER_TEMPERATURE_MEASUREMENT_UUID,
        BLECharacteristic::PROPERTY_INDICATE
    );
    thermometer_temperature_measurement->addDescriptor(new BLE2902());
    thermometer_tempRead = new BLECharacteristic(THERMOMETER_TEMP_READ_UUID,
                                                        BLECharacteristic::PROPERTY_WRITE | 
                                                        BLECharacteristic::PROPERTY_READ
                                                        );
    thermometer_service->addCharacteristic(thermometer_tempRead);
    thermometer_tempRead->setValue(&INITIAL_STATE,1);
    thermometer_service->start();
}