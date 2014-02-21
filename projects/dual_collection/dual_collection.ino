#include <MsTimer2.h>

const int DATASIZE = 500;
char state = 'N';
int n;
int data[DATASIZE];
unsigned long time[DATASIZE];
char moteid = 'A';

void sense();
void transmit();

void setup()
{
	Serial.begin(57600);
	Serial.setTimeout(10);
}

void sense() {
	Serial.println("Sensing");
	// Serial.print(moteid);
	// Serial.print(n);
	// Serial.print('/');
	// Serial.print(DATASIZE);
	if (n < DATASIZE && state == 'G') {

		// Read sensor value
		data[n] = analogRead(A0);
		time[n] = micros();
		// Serial.print('|');
		// Serial.print(data[n]);
		// Serial.print('@');
		// Serial.print(time[n]);
		// Serial.println('G');
		
		++n;
	}
	if	(n >= DATASIZE) {
		// Serial.println('D');
		state = 'T';
	}
}

void transmit() {
	// B gets to wait till A finishes
	if (moteid == 'B') {
		delay(1*DATASIZE / 2);
	}
	
	for (int i=0; i < DATASIZE; i++) {
		// Send it
		Serial.print(moteid);
		Serial.print(time[i]);
		Serial.print("\t");
		Serial.println(data[i]);
	}
	state = 'N';
}

void loop() {
	char inchar = Serial.read();
	
	if (inchar == 'S' && state == 'N') {
		state = 'G';
		n = 0;
		Serial.print("Start ");
		Serial.println(moteid);
		MsTimer2::set(100, sense);
		MsTimer2::start();
	}
	if (state == 'T') {
		Serial.print("Stop ");
		Serial.println(moteid);
		MsTimer2::stop();
		transmit();
	}
}
