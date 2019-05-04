#ifndef LED_H_
#define LED_H_
#include "Arduino.h"
class LED{
    private:
    const int ledPin;      // the number of the LED pin
	long onTime;     // milliseconds of on-time
	long offTime;    // milliseconds of off-time
    bool blink;

	int ledState;             		// ledState used to set the LED when blinking
	unsigned long previousMillis;  	// will store last time LED was updated

    public:
    LED(int pin, long on, long off, bool blink);
    void setBlink(bool blinkState);
    void setLEDState(int state);
    void updateLED();
};
#endif