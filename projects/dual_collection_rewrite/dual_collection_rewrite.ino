#include <MsTimer2.h>

#define DATASIZE 500

char moteid = 'B';
char state = 'N';
int fakedata = 0;

long time[500];
int data[500];

int n = 0;

void setup()
{
	Serial.begin(57600);
}

void sense() {
	if (n < DATASIZE) {
		data[n] = fakedata;
		time[n] = micros();
		fakedata++;
		n++;
	} else if (state != 'D') {
		state = 'D';
		n = 0;
	}
}

void loop() {
	char ichar = Serial.read();
	
	if (ichar == 'S' && state == 'N') {
		Serial.println("Starting timer");
		// Start the timer
		state = 'G';
		MsTimer2::set(10, sense);
		MsTimer2::start();
	} else if (state == 'D') {
		MsTimer2::stop();
		if (moteid == 'B') {
			delay(250);
		}
		for (int i=0; i < 500; i++) {
			Serial.print(moteid);
			Serial.print('\t');
			Serial.println(data[i]);
		}
		state = 'N';
	}
}
