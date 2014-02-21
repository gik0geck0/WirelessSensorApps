#include <MsTimer2.h>

const int datasize = 500;
int state = 0x01;
int n;
int* data;
unsigned long* time;
char moteid = 'A';

void sense();
void transmit();

void setup()
{
	data = (int*) malloc(datasize*sizeof(int));
	time = (unsigned long*) malloc(datasize*sizeof(unsigned long));
	Serial.begin(57600);
	Serial.setTimeout(10);
	MsTimer2::set(100, sense);
}

void sense() {
	Serial.println("Sensing");
	// Serial.print(moteid);
	// Serial.print(n);
	// Serial.print('/');
	// Serial.print(datasize);
	if (n < datasize && state == 0x02) {

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
	if	(n >= datasize) {
		// Serial.println('D');
		state = 0x03;
	}
}

void transmit() {
	// B gets to wait till A finishes
	if (moteid == 'B') {
		delay(1*datasize / 2);
	}
	
	for (int i=0; i < datasize; i++) {
		// Send it
		Serial.print(moteid);
		Serial.print(time[i]);
		Serial.print("\t");
		Serial.println(data[i]);
	}
	state = 0x01;
}

void loop()
{
	char inchar = Serial.read();
	
	if (inchar == 'S' && state != 0x02 && state != 0x03) {
		state = 0x02;
		n = 0;
		Serial.print("Start ");
		Serial.println(moteid);
		MsTimer2::start();
	}
	if (state == 0x03) {
		Serial.print("Stop ");
		Serial.println(moteid);
		MsTimer2::stop();
		transmit();
	}
}
