#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void x64calc(long long int n, float* arr[][3]);

int main() {

	float arr[][3] = { {0.0, 62.5, 10.1}, {60.0, 122.3, 5.5},{30.0, 160.7, 7.8} };
	
	int i = 0;
	/*for (i = 0; i < 3; i++) {
		printf("%f\n", arr[1][i]);
	}*/
	x64calc(3, arr);
	for (i = 0; i < 3; i++) {
		printf("%f\n", arr[i][2]);//final answer is stored in arr[i][2] might change later
	}

	return 0;
}
