#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

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

void loop();

int main()
{
	srand(0);
    for (int i=0; i<100000; i++) {
        loop();
    }
}

int ra = 4;
int carb = 3;
int cb = 2;

void loop()
{
	// Room for the two matricies
	int** a = (int**) malloc(ra*sizeof(int*));
    for(int i=0; i<ra; i++)
        a[i] = malloc(carb*sizeof(int));

	int** b = (int**) malloc(carb*sizeof(int*));
    for(int i=0; i<carb; i++)
        b[i] = malloc(ra*sizeof(int));

	// Show and randomly fill A
	printf("Matrix A:\n");
	for (int i=0; i<ra;i++) {
		for (int j=0; j<carb; j++) {
			a[i][j] = rand();
			printf("%i ", a[i][j]);
		}
		printf("\n");
	}
	
	// Show and randomly fill B
	printf("Matrix B:\n");
	for (int i=0; i<carb;i++) {
		for (int j=0; j<cb; j++) {
			b[i][j] = (int) rand();
			printf("%i ", b[i][j]);
		}
		printf("\n");
	}
	
	int startCalcTime = micros();
	int** result = matrixMult(a, b, ra, carb, cb);
	int endCalcTime = micros();
	
	// Show the mult result
	printf("Mult result:\n");
    int startTransTime = micros();
	for (int i=0; i<ra; i++) {
		for (int j=0; j<cb; j++) {
			printf("%i ", result[i][j]);
		}
		printf("\n");
	}
    int endTransTime = micros();

    printf("Calc time: %i\n", endCalcTime - startCalcTime);
    printf("With transmission: %i\n", endCalcTime - startCalcTime + endTransTime - startTransTime);

    for(int i=0; i<ra; i++)
        free(a[i]);
    free(a);

    for(int i=0; i<carb; i++) {
        free(result[i]);
        free(b[i]);
    }

    free(b);
    free(result);
}
