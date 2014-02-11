#include <Streaming.h>

void setup() {
	Serial.begin(57600);
	// 10s reset time
	Serial.setTimeout(1000);

	Serial << "Welcome to the ASCII-Mote system. Give me a letter, and ill tell you the ASCII value. Type 'quit' to stop." << endl;
}

int recstatus = 0;
char receiveBuffer[10];
void loop() {
	
	// Get the letter
	recstatus = Serial.readBytes(receiveBuffer, 1);
	if (recstatus > 0) {
		// Print out the numerical value
		Serial << (uint8_t) receiveBuffer[0] << endl;
	}
}