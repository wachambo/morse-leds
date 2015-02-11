// start at ASCII 43 and finish at ASCII 90
#define START_ASCII	43
#define END_ASCII	90

// output pin that the LED is attached to
const int pin = 13;

// takes a string and changes it in UPPERCASE
void uppercase(char* str)
{
	for ( ; *str; str++)
		if (*str >= 97 && *str <= 122) // if lowecase letter
			*str -= 32;
}

char* alphabet[] = { 
".-.-.", // +
"--..--", // ,
"-....-", // -
".-.-.-", // .
"-..-.", // /
"-----", // 0
".----", // 1
"..---", // 2
"...--", // 3
"....-", // 4
".....", // 5
"-....", // 6
"--...", // 7
"---..", // 8
"----.", // 9
"---...", // :
"-.-.-.", // ;
"-..-.", // / (should be < but used / to fill)
"-...-", // =
"-..-.", // / (should be > but used / to fill)
"..--..", // ?
".--.-.", // @
".-", // A
"-...", // B
"-.-.", // C
"-..", // D
".", // E
"..-.", // F
"--.", // G
"....", // H
"..", // I
".---", // J
"-.-", // K
".-..", // L
"--", // M
"-.", // N
"---", // O
".--.", // P
"--.-", // Q
".-.", // R
"...", // S
"-", // T
"..-", // U
"...-", // V
".--", // W
"-..-", // X
"-.--", // Y
"--.."}; // Z

void setup() {
	Serial.begin(9600);

	// initialize digital pin as an output.
	pinMode(pin, OUTPUT);

	char text[] = "esto es UNA prueba +\0";
	uppercase(text);

	char *c = text;	//char pointer to the begging of array text
	for ( ; *c; c++)
		if ((*c >= START_ASCII) && (*c <= END_ASCII)) {
			//Serial.println(*c);
			Serial.print(alphabet[*c - START_ASCII]);
		}
}

void loop() {}