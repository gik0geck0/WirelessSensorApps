#include <MsTimer2.h>
void senseAndTransmit();

void setup() {
	Serial.begin(57600);
	MsTimer2::set(10, senseAndTransmit);
	MsTimer2::start();
}
int xVal;
void senseAndTransmit() {
	// Read sensor value
	xVal = analogRead(0);

}

void loop() {
	// Change it
	xVal = -999;
	
	// Delay
	delay(8);

	// Send it
	Serial.print(micros());
	Serial.print("\t");
	Serial.println(xVal);
}
