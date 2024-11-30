#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

extern void x64calc(long long int n, float arr[][3], int* ans);

void getAcceleration(long long int n, float arr[][3], float* ans) {
    int i;
    float delta_v/*, acceleration*/;

    for (i = 0; i < n; i++) {
        delta_v = (arr[i][1] - arr[i][0]) * 1000 / 3600;
        ans[i] = delta_v / arr[i][2];

        /*printf("[Row %d] vf = %.2f | vi = %.2f | t = %.2f | a = %.2f m/s^2\n",
            i + 1, arr[i][1], arr[i][0], arr[i][2], acceleration);*/
    }
}

int main() {
    unsigned long long int ARRAY_SIZE;
    printf("\nEnter array size: ");
    scanf_s("%llu", &ARRAY_SIZE);
    size_t ARRAY_BYTES = ARRAY_SIZE * 3 * sizeof(float);
    clock_t start, end;
    double time_taken;
    int i;

    float (*arr)[3] = malloc(ARRAY_BYTES);

    float* ansC = (float*)malloc(ARRAY_SIZE * sizeof(float));
    int* ans64 = (int*)malloc(ARRAY_SIZE * sizeof(float));

    srand((unsigned int)time(NULL));
    for (i = 0; i < 10; i++) {
        arr[i][0] = (float)rand() / (RAND_MAX / 50.0f);
        arr[i][1] = 50.0f + (float)rand() / (RAND_MAX / 50.0f);
        arr[i][2] = 5.0f + (float)rand() / (RAND_MAX / 10.0f);

    }


    // C Execution
    //------------------------
    printf("\nC Execution\n");
    start = clock();
    getAcceleration(ARRAY_SIZE, arr, ansC);
    end = clock();
    time_taken = ((double)(end - start) * 10000 / CLOCKS_PER_SEC);
    for (i = 0; i < 10; i++) {
        printf("[Row %d] vf = %.2f | vi = %.2f | t = %.2f | a = %d m/s^2\n",
            i + 1, arr[i][1], arr[i][0], arr[i][2], (int)round(ansC[i]));
    }

    printf("[C] Time: %lf ms\n", time_taken);


    // x86-64 Execution
    //------------------------
    printf("\nx86-64 Execution\n");
    start = clock();
    x64calc(ARRAY_SIZE, arr, ans64);
    end = clock();
    time_taken = ((double)(end - start) * 10000 / CLOCKS_PER_SEC);

    for (i = 0; i < 10; i++) {
        printf("[Row %d] Final answer: %d m/s^2\n", i + 1, ans64[i]);
    }
    printf("[x86-64] Time: %lf ms\n", time_taken);

    

    return 0;
}
