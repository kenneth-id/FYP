#include "BIT_HW.h"

uint8_t bit_1, bit_2;

void initBIT_HW(){
    pinMode(BIT1_HW, INPUT);
    pinMode(BIT2_HW, INPUT);
}

void readBIT_HW(){
    bit_1 = digitalRead(BIT1_HW);
    bit_2 = digitalRead(BIT2_HW);
}

void detect_sensor_module(){
    if(bit_1 == LOW && bit_2 == LOW){
        sensor_mode = 0;
    } else if(bit_1 == LOW && bit_2 == HIGH){
        sensor_mode = 1;
    } else if(bit_1 == HIGH && bit_2 == LOW){
        sensor_mode = 2;
    } else if(bit_1 == HIGH && bit_2 == HIGH){
        sensor_mode = 3;
    }

    switch(sensor_mode){
        case 0:
        Serial.println("No sensor detected. Please try again.");
        setLED(HIGH, HIGH, HIGH);
        break;
        
        case 1:
        Serial.println("Heartbeat Sensor detected.");
        setLED(HIGH, LOW, LOW);
        break;

        case 2:
        Serial.println("Temperature Sensor detected.");
        setLED(LOW, HIGH, LOW);
        break;

        case 3:
        Serial.println("ECG Sensor detected.");
        setLED(LOW, LOW, HIGH);
        break;
    }

}