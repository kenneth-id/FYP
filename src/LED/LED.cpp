#include "LED.h"

void initLED() {
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
}

void setLED(uint8_t L1, uint8_t L2, uint8_t L3) {
    digitalWrite(LED1, L1);
    digitalWrite(LED2, L2);
    digitalWrite(LED3, L3);
}


void initRGB() {
    // ledcAttachPin(RGB_RED, 1);
    // ledcAttachPin(RGB_GREEN, 2);
    // ledcAttachPin(RGB_BLUE, 3);
    // ledcSetup(1, 12000, 8);
    // ledcSetup(2, 12000, 8);
    // ledcSetup(3, 12000, 8);
    pinMode(RGB,OUTPUT);
    pinMode(RGB_RED, OUTPUT);
    pinMode(RGB_GREEN, OUTPUT);
    pinMode(RGB_BLUE, OUTPUT);
}

void setRGB(uint8_t RGBP, uint8_t R, uint8_t G, uint8_t B){
    digitalWrite(RGB, RGBP);
    digitalWrite(RGB_RED, R);
    digitalWrite(RGB_GREEN, G);
    digitalWrite(RGB_BLUE, B);
    // ledcWrite(1, R);
    // ledcWrite(2, G);
    // ledcWrite(3, B);
}

void blink(uint8_t pin, uint_fast32_t interval){
    digitalWrite(pin,HIGH);
    delay(interval);
    digitalWrite(pin,LOW);
    delay(interval);
}  