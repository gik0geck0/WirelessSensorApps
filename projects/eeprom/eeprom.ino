
#include <EEPROM.h>

void addP() {
	// increment the int16 in eeprom by one
	byte* a = (byte*) malloc(2*sizeof(byte));
	a[0] = EEPROM.read(0);
	// a[1] = EEPROM.read(1);
	// ++(*((int*) a));
	++(*a);
	EEPROM.write(0, a[0]);
	// EEPROM.write(1, a[1]);
	free(a);
}

int getP() {
	byte* a = (byte*) malloc(2*sizeof(byte));
	a[0] = EEPROM.read(0);
	// a[1] = EEPROM.read(1);
	// int r = *((int*) a);
	int r = (int) a[0];
	free(a);
	return r;
}

void setup()
{
	
	pinMode(13, OUTPUT);
	Serial.begin(57600);
	Serial.setTimeout(1);
	
	if (EEPROM.read(0) == 255 && EEPROM.read(1) == 255) {
		// initialize our int16 to count 'P's
		EEPROM.write(0,0);
		EEPROM.write(0,1);
	}
	
	int p = getP();
	Serial.println(p);
}

char receive_byte[10];
int recstatus;

void loop()
{
	recstatus = Serial.readBytes(receive_byte, 1);
	if (recstatus == 1) {
		if (receive_byte[0] == 'P') {
			addP();
		}
	}
}
