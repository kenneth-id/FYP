#ifndef RGB_H_
#define RGB_H_
#include "Arduino.h"

#define RGB_RED     18
#define RGB_GREEN   17
#define RGB_BLUE    16
#define RGB_PIN     19

class RGB{
    private:
	long onTime;     // milliseconds of on-time
	long offTime;    // milliseconds of off-time
    bool blink;

    int redPWM;
    int greenPWM;
    int bluePWM;

	int ledState;             		// ledState used to set the LED when blinking
	unsigned long previousMillis;  	// will store last time LED was updated
    void writeRGB(); // analog write the PWM values

    public:
    RGB(int red, int green, int blue, long on, long off, bool blink);
    void setBlink(bool blinkState);
    void setRGBState(int state);
    void setColor(int red, int green, int blue);
    void updateRGB();
};
#endif