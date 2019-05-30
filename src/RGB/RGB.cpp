#include "RGB.h"

RGB::RGB(int red, int green, int blue, long on, long off, bool blink){
	pinMode(RGB_RED, OUTPUT);
    pinMode(RGB_GREEN, OUTPUT);     
	pinMode(RGB_BLUE, OUTPUT);     
	pinMode(RGB_PIN, OUTPUT);

    this->redPWM=red;
    this->greenPWM=green;
    this->bluePWM=blue;

	this->blink= blink;
	onTime = on;
	offTime = off;
	ledState = LOW; 
	previousMillis = 0;
}

void RGB::setBlink(bool blinkState){
    this->blink= blinkState;
}

void RGB::setRGBState(int state){
    this->ledState= state;
}

void RGB::setColor(int red, int green, int blue){
    this->redPWM=red;
    this->greenPWM=green;
    this->bluePWM=blue;
}

void RGB::writeRGB(){
    digitalWrite(RGB_RED,redPWM);
    digitalWrite(RGB_GREEN,greenPWM);
    digitalWrite(RGB_BLUE,bluePWM);
    digitalWrite(RGB_PIN,ledState);
}

void RGB::updateRGB(){
    // check to see if it's time to change the state of the LED
    if(blink==true){
        unsigned long currentMillis = millis();
        if((ledState == HIGH) && (currentMillis - previousMillis >= onTime)){
            ledState = LOW;  // Turn it off
            previousMillis = currentMillis;  // Remember the time
            writeRGB();  // Update the actual LED
        }
        else if ((ledState == LOW) && (currentMillis - previousMillis >= offTime)){
            ledState = HIGH;  // turn it on
            previousMillis = currentMillis;   // Remember the time
            writeRGB();	  // Update the actual LED
        }
    }
    else{
        writeRGB();
    }
}