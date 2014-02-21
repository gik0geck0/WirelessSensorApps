#include <MsTimer2.h>

#define BSIZE 10
int bufferA[BSIZE];
int bufferB[BSIZE];

unsigned long timeA[BSIZE];
unsigned long timeB[BSIZE];

// 1 mean using buffer A. 2 means using buffer B.
int readState = 2;
int writeState = 1;

int readIndex = BSIZE;
int writeIndex = 0;

int fakeRead = 0;

void sense();

void setup()
{
    Serial.begin(57600);
	MsTimer2::set(1, sense);
	MsTimer2::start();
}

void sense() {
	// Serial.print("Trying to write buffer ");
	// Serial.print( (writeState == 1) ? 'A' : 'B');
	// Serial.print(" at index ");
	// Serial.println(writeIndex);
    // Try to write
    if (writeIndex < BSIZE) {
        // We have room to write
        if (writeState == 1) {
            // Write to A
            bufferA[writeIndex] = fakeRead; // analogRead(0);
			timeA[writeIndex] = micros();
        } else {
            bufferB[writeIndex] = fakeRead; // analogRead(0);
			timeB[writeIndex] = micros();
        }
        fakeRead++;
        writeIndex++;
    } else {
        // We need to try to switch buffers
		if (writeState == 1) {
            // Can we switch to bufferB?
            if (readState == 1 || readIndex == BSIZE) {
                // The writer has moved on to the current read buffer OR the writer is done with its buffer
                writeState = 2;
                writeIndex = 0;
            } else {
                // The writer is still using its buffer
            }
        } else {
            // Can we switch to bufferA
            if (readState == 2 || readIndex == BSIZE) {
                writeState = 1;
                writeIndex = 0;
            } else {
                // The writer is still using its buffer
            }
        }
		
		/*
        if (readIndex == BSIZE) {
            // This indicates that the reader is done with its buffer. That's good. Change buffers
            if (writeState == 1) {
                writeState = 2;
            } else {
                writeState = 1;
            }
            writeIndex = 0;
        } else {
            // The read is not done. Do nothing. We need to keep buffer use synchronized
        }
		*/
    }
}

void loop() {
	// Serial.print("Trying to read buffer ");
	// Serial.print( (readState == 1) ? 'A' : 'B');
	// Serial.print(" at index ");
	// Serial.println(readIndex);
    // Try to read
    if (readIndex < BSIZE) {
        // We have places to read
        if (readState == 1) {
            // read from A
            Serial.print(bufferA[readIndex]);
			Serial.print('\t');
			Serial.println(timeA[readIndex]);
        } else {
            Serial.print(bufferB[readIndex]);
			Serial.print('\t');
			Serial.println(timeB[readIndex]);
        }
        readIndex++;
    } else {
        // We need to try to switch buffers
        if (readState == 1) {
            // Can we switch to bufferB?
            if (writeState == 1 || writeIndex == BSIZE) {
                // The writer has moved on to the current read buffer OR the writer is done with its buffer
                readState = 2;
                readIndex = 0;
            } else {
                // The writer is still using its buffer
            }
        } else {
            // Can we switch to bufferA
            if (writeState == 2 || writeIndex == BSIZE) {
                readState = 1;
                readIndex = 0;
            } else {
                // The writer is still using its buffer
            }
        }
    }
	// delay(8);
}
