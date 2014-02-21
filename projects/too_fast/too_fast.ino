#include <MsTimer2.h>
void senseAndTransmit();

void setup() {
	Serial.begin(57600);
	MsTimer2::set(1, senseAndTransmit);
	MsTimer2::start();
}
int xVal;
void senseAndTransmit() {
	// Read sensor value
	xVal = analogRead(0);
	Serial.println(xVal);
}

void loop() {
}
