/*
 	MorseLed.h - Library for flashing	MorseLed code.
  	Created by David A. Mellis, November 2, 2007.
  	Released into the public domain.
*/
#ifndef	MorseLed_h
#define	MorseLed_h

#include "Arduino.h"

class MorseLed
{
public:
	MorseLed(int pin);
    void dot();
    void dash();
private:
    int _pin;
};

MorseLed:MorseLed(int pin)
{
	pinMode(pin, OUTPUT);
	_pin = pin;
}

void MorseLed::dot()
{
	digitalWrite(_pin, HIGH);
	delay(250);
	digitalWrite(_pin, LOW);
	delay(250);  
}

void MorseLed::dash()
{
	digitalWrite(_pin, HIGH);
	delay(1000);
	digitalWrite(_pin, LOW);
	delay(250);
}

#endif