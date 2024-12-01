#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>

extern void x64calc(long long int n, float arr[][3], int* ans);

void getAcceleration(unsigned long long array_size, float arr[][3], float* ans) {
    int i;
    float delta_v;

    for (i = 0; i < array_size; i++) {
        delta_v = (arr[i][1] - arr[i][0]) * 1000 / 3600; 
        ans[i] = delta_v / arr[i][2];  
        
        //printf("Row %d | %d m/s^2\n", i + 1, (int)roundf(ans[i]));
    }
}

void cmpArr(long long int n, float* c, int* x64) {
    int i;
    int error = 0;

    for (i = 0; i < n; i++) {
        int roundedC;
        float fraction = c[i] - floorf(c[i]);  

        if (fraction == 0.5f) {
            roundedC = (int)(roundf(c[i] / 2) * 2);
        }
        else {
            roundedC = (int)roundf(c[i]);
        }

        //printf("Row %d | Original value: %.2f | Rounded value: %d | x64 value: %d\n",
         //   i + 1, c[i], roundedC, x64[i]);

        if (roundedC != x64[i]) {
            error = 1;
        }
    }

    if (error == 1) {
        printf("There are errors in the acceleration values.\n");
    }
    else {
        printf("All acceleration values are correct!\n");
    }
}

void getTxt(const char* filename, unsigned long long int* array_size, float (**arr)[3]) {
    //https://www.geeksforgeeks.org/c-program-to-read-contents-of-whole-file/
    FILE* ptr = fopen(filename, "r");
    if (ptr == NULL) {
        printf("Cannot open file %s.\n", filename);
        exit(1);
    }

    if (fscanf_s(ptr, "%llu", array_size) != 1) {
        printf("Read failure\n");
        fclose(ptr);
        exit(1);
    }

    printf("File: %s\n", filename);
    printf("Array size: %llu\n", *array_size);

    *arr = malloc((*array_size) * 3 * sizeof(float));
    if (*arr == NULL) {
        printf("Malloc failure\n");
        fclose(ptr);
        exit(1);
    }

    for (unsigned long long i = 0; i < *array_size; i++) {
        if (fscanf_s(ptr, "%f %f %f", &(*arr)[i][0], &(*arr)[i][1], &(*arr)[i][2]) != 3) {
            printf("Invalid input\n");
            fclose(ptr);
            free(*arr);
            exit(1);
        }
    }

    fclose(ptr);
    printf("Successfully read %llu rows from %s\n", *array_size, filename);
}

void getInput(unsigned long long int* array_size, float (**arr)[3]) {
    printf("Enter the number of rows: ");
    if (scanf_s("%llu", array_size) != 1) {
        printf("Invalid input.\n");
        exit(1);
    }

    *arr = malloc(*array_size * sizeof(float[3]));
    if (*arr == NULL) {
        printf("Malloc failure\n");
        exit(1);
    }

    printf("Enter the values (vi vf t) for each row:\n");
    for (unsigned long long i = 0; i < *array_size; i++) {
        printf("Row %llu: ", i + 1);
        if (scanf_s("%f %f %f", &(*arr)[i][0], &(*arr)[i][1], &(*arr)[i][2]) != 3) {
            printf("Invalid input.\n");
            free(*arr); 
            exit(1);
        }
    }
}

void dispMenu() {
    printf("Choose an option:\n");
    printf("[1] Insert an array\n");
    printf("[2] Read from 10.txt\n");
    printf("[3] Read from 100.txt\n");
    printf("[4] Read from 1000.txt\n");
    printf("[5] Read from 10000.txt\n");
    printf("Enter your choice: ");
}

int main() {
    unsigned long long int array_size = 0;
    float (*arr)[3] = NULL; 
    int choice;

    dispMenu();
    if (scanf_s("%d", &choice) != 1) {
        printf("Error: Invalid input.\n");
        return 1;
    }

    switch (choice) {
    case 1:
        getInput(&array_size, &arr);
        break;
    case 2:
        getTxt("10.txt", &array_size, &arr);
        break;
    case 3:
        getTxt("100.txt", &array_size, &arr);
        break;
    case 4:
        getTxt("1000.txt", &array_size, &arr);
        break;
    case 5:
        getTxt("10000.txt", &array_size, &arr);
        break;
    default:
        printf("Error: Invalid choice.\n");
        return 1;
    }

    float* ansC = malloc(array_size * sizeof(float));
    int* ans64 = malloc(array_size * sizeof(int));

    if (ansC == NULL || ans64 == NULL) {
        printf("Error: Memory allocation failed for result arrays.\n");
        free(arr);
        exit(1);
    }

    //https://stackoverflow.com/questions/1739259/how-to-use-queryperformancecounter

    LARGE_INTEGER start, end, freq;
    double c_total = 0.0, time_taken, c_avg;
    double x_total = 0.0, x_avg;

    QueryPerformanceFrequency(&freq);

    for (int i = 0; i < 30; i++) {
        QueryPerformanceCounter(&start);

        getAcceleration(array_size, arr, ansC);

        QueryPerformanceCounter(&end);

        time_taken = ((double)(end.QuadPart - start.QuadPart) * 1000000.0) / freq.QuadPart;
        c_total += time_taken;
    }
    c_avg = c_total / 30;

    for (int i = 0; i < 30; i++) {
        QueryPerformanceCounter(&start);

        x64calc(array_size, arr, ans64);

        QueryPerformanceCounter(&end);

        time_taken = ((double)(end.QuadPart - start.QuadPart) * 1000000.0) / freq.QuadPart;
        x_total += time_taken;
    }

    x_avg = x_total / 30;

    for (unsigned long long j = 0; j < array_size; j++) {
        printf("[%llu] acceleration = %d\n", j, ans64[j]);
    }

    printf("\n----------------------------------------\n");
    printf("\nRESULTS \n\n");
    printf("Number of rows: %llu\n", array_size);
    printf("Correctness check: \n");
    cmpArr(array_size, ansC, ans64);

    printf("\nC Performance\n");
    printf("Average time taken (30 runs): %.2f microseconds\n", c_avg);
    printf("Total time taken (30 runs):   %.2f microseconds\n", c_total);

    printf("\nx86-64 Performance\n");
    printf("Average time taken (30 runs): %.2f microseconds\n", x_avg);
    printf("Total time taken (30 runs):   %.2f microseconds\n", x_total);

    printf("\n----------------------------------------\n");

    return 0;
}

