#include "BitVerification.h"

BitVerification::BitVerification(){
    pinMode(BIT1_HW, INPUT);
    pinMode(BIT2_HW, INPUT);

    readBits();
    state= NOSENSOR;

    bit_verification_service= FYP_server->createService(BIT_VERIFICATION_SERVICE_UUID);
    bit_verification_characteristic= bit_verification_service->createCharacteristic(BIT_VERIFICATION_CHARACTERISTIC_UUID,BLECharacteristic::PROPERTY_READ);
    bit_verification_characteristic->setValue(state);
    bit_verification_service->start();
}

int BitVerification::getState(){
    return state;
} 

void BitVerification::updateState(){
    readBits();

    if(bit_1 == LOW && bit_2 == LOW){
        state = NOSENSOR;
    } else if(bit_1 == LOW && bit_2 == HIGH){
        state = HEARTRATE;
    } else if(bit_1 == HIGH && bit_2 == LOW){
        state = TEMPERATURE;
    } else if(bit_1 == HIGH && bit_2 == HIGH){
        state = ECG;
    }

    bit_verification_characteristic->setValue(state);
}

void BitVerification::readBits(){
    bit_1 = digitalRead(BIT1_HW);
    bit_2 = digitalRead(BIT2_HW);
}