#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int sum(int* list, int length) {
	int total = 0;
	for (int i=0; i<length; i++) {
		total += list[i];
	}
	return total;
}

int* zipWithMult(int* listA, int* listB, int length) {
	int* retList = (int*) malloc(length*sizeof(int));
	for (int i=0; i<length; i++) {
		retList[i] = listA[i] * listB[i];
	}
	return retList;
}

int** matrixMult(int** a, int** b, int ra, int carb, int cb) {
	int** retMult = (int**) malloc(ra*sizeof(int*));
	for (int i=0; i<ra; i++) {
        retMult[i] = (int*) malloc(cb*sizeof(int));
		for (int j=0; j<cb; j++) {
			// The value in [i,j] is...
            int* zwm = zipWithMult(a[i], b[j], carb);
			retMult[i][j] = sum(zwm, carb);
            free(zwm);
		}
	}
	return retMult;
}

int micros() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return 100000*t.tv_sec + t.tv_usec;
}

void main()
{
    for (int i = 0; i < 10; i++) {
        loop();
    }
}

int ra = 10;
int carb = 10;
int cb = 10;
int xInput;
int analogRead(int pin) { return pin; }

unsigned long lastTime;
unsigned long currentTime;
void loop()
{
	// Let's do matrix math to display why delay() is inaccurate. Specifically if we have lots of code
	int** a = (int**) malloc(ra*sizeof(int*));
    for(int i=0; i<ra; i++)
        a[i] = (int*) malloc(carb*sizeof(int));
	int** b = (int**) malloc(carb*sizeof(int*));
    for(int i=0; i<carb; i++)
        b[i] = (int*) malloc(cb*sizeof(int));
	// Randomly fill A
	for (int i=0; i<ra;i++) { for (int j=0; j<carb; j++) {
			a[i][j] = rand();
	} }
	// Randomly fill B
	for (int i=0; i<carb;i++) { for (int j=0; j<cb; j++) {
			b[i][j] = rand();
	} }
	int** result = matrixMult(a, b, ra, carb, cb);
	// In order to keep the mult result, we need to use it. So sum the matrix, and transmit that.
	int sum = 0;
	for (int i=0; i<ra; i++) {
		for (int j=0; j<cb; j++) {
			sum += result[i][j];
		}
	}
	printf("Ignore: %i\n", sum);
	
	// Get sensor reading, and see when it happened. I think it's technically more accurate to time BEFORE the analogRead, since it spends more time in the ADC
	currentTime = micros();
	xInput = analogRead(0);
	
	long tDiff = currentTime - lastTime;
	
	printf("Val: %i tDiff: %i\n", xInput, tDiff);
	
	for(int i=0; i<ra; i++)
        free(a[i]);
    free(a);

    for(int i=0; i<carb; i++) {
        free(result[i]);
        free(b[i]);
    }

    free(b);
    free(result);
	
	// delay(100);
}
