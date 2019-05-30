#include "LED.h"

LED::LED(int pin, long on, long off,bool blink): ledPin(pin){
    // ledPin = pin;
	pinMode(ledPin, OUTPUT);     
	this->blink= blink;
	onTime = on;
	offTime = off;
	ledState = LOW; 
	previousMillis = 0;
}

void LED::setBlink(bool blinkState){
    this->blink= blinkState;
}

void LED::setLEDState(int state){
    this->ledState= state;
}

void LED::updateLED(){
    // check to see if it's time to change the state of the LED
    if(blink==true){
        unsigned long currentMillis = millis();
        if((ledState == HIGH) && (currentMillis - previousMillis >= onTime)){
            ledState = LOW;  // Turn it off
            previousMillis = currentMillis;  // Remember the time
            digitalWrite(ledPin, ledState);  // Update the actual LED
        }
        else if ((ledState == LOW) && (currentMillis - previousMillis >= offTime)){
            ledState = HIGH;  // turn it on
            previousMillis = currentMillis;   // Remember the time
            digitalWrite(ledPin, ledState);	  // Update the actual LED
        }
    }
    else{
        digitalWrite(ledPin, ledState);
    }
}