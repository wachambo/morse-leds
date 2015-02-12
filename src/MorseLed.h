/*
 	MorseLed.h - Library for flashing Morse code.
  	Created by Alejandro Blasco 
  	Released into the public domain.
*/
#ifndef	MorseLed_h
#define	MorseLed_h

// start at ASCII 43 and finish at ASCII 90
#define START_ASCII	43
#define END_ASCII	90
#define SPACE		32
#define TIME_MS		250

#include "Arduino.h"
#include <avr/pgmspace.h>

// table of morse codes in PROGMEM
PROGMEM const char
	str_0[] = ".-.-.", 		// +
	str_1[] = "--..--", 	// ,
	str_2[] = "-....-", 	// -
	str_3[] = ".-.-.-", 	// .
	str_4[] = "-..-.", 		// /
	str_5[] = "-----",		// 0
	str_6[] = ".----", 		// 1
	str_7[] = "..---",		// 2
	str_8[] = "...--", 		// 3
	str_9[] = "....-", 		// 4
	str_10[] = ".....", 	// 5
	str_11[] = "-....", 	// 6
	str_12[] = "--...", 	// 7
	str_13[] = "---..", 	// 8
	str_14[] = "----.", 	// 9
	str_15[] = "---...", 	// :
	str_16[] = "-.-.-.", 	// ;
	str_17[] = "-..-.", 	// / (should be < but used / to fill)
	str_18[] = "-...-", 	// =
	str_19[] = "-..-.", 	// / (should be > but used / to fill)
	str_20[] = "..--..", 	// ?
	str_21[] = ".--.-.",	// @
	str_22[] = ".-", 		// A
	str_23[] = "-...", 		// B
	str_24[] = "-.-.", 		// C
	str_25[] = "-..", 		// D
	str_26[] = ".", 		// E
	str_27[] = "..-.", 		// F
	str_28[] = "--.", 		// G
	str_29[] = "....", 		// H
	str_30[] = "..", 		// I
	str_31[] = ".---", 		// J
	str_32[] = "-.-", 		// K
	str_33[] = ".-..", 		// L
	str_34[] = "--", 		// M
	str_35[] = "-.", 		// N
	str_36[] = "---", 		// O
	str_37[] = ".--.",		// P
	str_38[] = "--.-", 		// Q
	str_39[] = ".-.", 		// R
	str_40[] = "...", 		// S
	str_41[] = "-", 		// T
	str_42[] = "..-", 		// U
	str_43[] = "...-", 		// V
	str_44[] = ".--", 		// W
	str_45[] = "-..-", 		// X
	str_46[] = "-.--", 		// Y
	str_47[] = "--.."; 		// Z

const char * const alphabet[] PROGMEM = {
	str_0,str_1,str_2,str_3,str_4,str_5,str_6,str_7,str_8,str_9,str_10,
	str_11,str_12,str_13,str_14,str_15,str_16,str_17,str_18,str_19,str_20,
	str_21,str_22,str_23,str_24,str_25,str_26,str_27,str_28,str_29,str_30,
	str_31,str_32,str_33,str_34,str_35,str_36,str_37,str_38,str_39,str_40,
	str_41,str_42,str_43,str_44,str_45,str_46,str_47 }; 	

class MorseLed
{
// members
private:
    int _pin;

// functions
public:
	MorseLed(int pin);
    void dot();
    void dash();
    void space();
    void encode(char *);
private:
    void uppercase(char *);
};

MorseLed::MorseLed(int pin)
{
	pinMode(pin, OUTPUT);
	_pin = pin;
}

/** Emule a dot 
 */
void MorseLed::dot()
{
	digitalWrite(_pin, HIGH);
	delay(TIME_MS);
	digitalWrite(_pin, LOW); 
	delay(TIME_MS);  
}

/** Emule a dash 
 */
void MorseLed::dash()
{
	digitalWrite(_pin, HIGH);
	delay(3*TIME_MS);
	digitalWrite(_pin, LOW);
	delay(TIME_MS);
}

/** Emule a space 
	(actually is 3xTIME_MS but we are adding 
	always a TIME_MS after each element(dot/dash))
 */
void MorseLed::space()
{
	digitalWrite(_pin, LOW);
	delay(2*TIME_MS);
}


/** Encode a string to Morse using dots and dashes
	param	text
 */
void MorseLed::encode(char *str)
{
	char buffer[5];		// buffer for store a morse code from flash

	uppercase(str);
	
	for (char *c = str; *c; c++) {
		Serial.print(*c);
		if (*c == SPACE) { 
			Serial.println(F("   ")); 
			space();
			continue; 
		}
		if ((*c >= START_ASCII) && (*c <= END_ASCII)) { // the char is ascii
			// retrieve from flash
			strcpy_P(buffer, (char*)pgm_read_word(&(alphabet[*c - START_ASCII]))); // Necessary casts and dereferencing, just copy. 
			Serial.println(buffer);

			for (char *b = buffer; *b; b++)
				if (*b == '.') dot();
				else if (*b == '-') dash(); 
		}
	}
}


/** Transforms the input param string to Uppercase
	param[in/out]	string
 */
void MorseLed::uppercase(char *str)
{
	for ( ; *str; str++)
		if (*str >= 97 && *str <= 122) // if lowecase letter
			*str -= 32;
}

#endif