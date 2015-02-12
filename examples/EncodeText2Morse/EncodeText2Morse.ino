#include "MorseLed.h"

// output pin that the LED is attached to
const int pin = 13;


void setup() {
	Serial.begin(9600);

	// initialize digital pin as an output.
	pinMode(pin, OUTPUT);

	// TODO: Serial.read ??
	char text[] = "Coding Paris";

	// a MorseLed instance with the pin
	MorseLed morse(pin);

	Serial.println(text);
	morse.encode(text);
}

void loop() {}