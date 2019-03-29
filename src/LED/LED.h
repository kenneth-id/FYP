#ifndef LED_H_
#define LED_H_

#include "Arduino.h"

#define LED1        12
#define LED2        13
#define LED3        14
#define RGB_RED     18
#define RGB_BLUE    16
#define RGB_GREEN   17
#define RGB         19

void initLED();
void initRGB();
void setLED(uint8_t L1, uint8_t L2, uint8_t L3);
void setRGB(uint8_t RGBP, uint8_t R, uint8_t G, uint8_t B);
void blink(uint8_t pin, uint_fast32_t interval);

#endif