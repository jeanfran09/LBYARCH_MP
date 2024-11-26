#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void x64calc(long long int n, float* arr[][3]);

void getAcceleration(long long int n, float arr[][3], float* x) {
	int i;
	float delta_v, acceleration;

	for (i = 0; i < n; i++) {
		delta_v = (arr[i][1] - arr[i][0]) * 1000 / 3600;
		acceleration = delta_v / arr[i][2];

		x[i] = acceleration;

		printf("[Row %d] a = %.2f m/s^2\n", i + 1, acceleration);
	}
}

int main() {
	unsigned long long int ARRAY_SIZE = 3;
	unsigned long long int ARRAY_BYTES = ARRAY_SIZE * sizeof(float);
	clock_t start, end;
	double time_taken;
	int i;

	float arr[][3] = { {0.0, 62.5, 10.1}, {60.0, 122.3, 5.5},{30.0, 160.7, 7.8} };

	//declare array to store the acceleration per row
	float* x;
	x = (float*)malloc(ARRAY_BYTES);
	
	for (i = 0; i < ARRAY_SIZE; i++) {
		x[i] = 0.0; 
	}

	//getAcceleration(ARRAY_SIZE, arr, x);

	/*
	int i = 0;
	/*for (i = 0; i < 3; i++) {
		printf("%f\n", arr[1][i]);
	}
	x64calc(3, arr);
	for (i = 0; i < 3; i++) {
		printf("%f\n", arr[i][2]);//final answer is stored in arr[i][2] might change later
	}
	*/

	//C 
	//------------------------
	start = clock();
	getAcceleration(ARRAY_SIZE, arr, x);
	end = clock();
	time_taken = ((double)(end - start) * 1000 / CLOCKS_PER_SEC);

	printf("%lf ms\,\n", time_taken);
	//sanity check
	//print the values of x
	for (i = 0; i < ARRAY_SIZE; i++) {
		printf("[%d] Acceleration = %lf\n", i + 1, x[i]);
	}

	//x86-64
	//------------------------
	//reinitialize the array
	//float arr[][3] = {{0.0, 62.5, 10.1}, {60.0, 122.3, 5.5},{30.0, 160.7, 7.8}};

	start = clock();
	x64calc(3, arr);
	end = clock();
	time_taken = ((double)(end - start) * 1000 / CLOCKS_PER_SEC);
	printf("%lf ms\,\n", time_taken);
	for (i = 0; i < 3; i++) {
		printf("%f\n", arr[i][2]);//final answer is stored in arr[i][2] might change later
	}
	return 0;
}
