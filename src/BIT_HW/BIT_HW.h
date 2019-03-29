#ifndef BIT_HW_H_
#define BIT_HW_H_

#include "Arduino.h"
#include "../LED/LED.h"

#define BIT1_HW       33
#define BIT2_HW       34

extern int sensor_mode;

void initBIT_HW();
void readBIT_HW();
void detect_sensor_module();

#endif