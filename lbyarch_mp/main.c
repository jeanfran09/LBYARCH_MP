#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

extern void x64calc(long long int n, float** arr, int* ans);

void getAcceleration(unsigned long long array_size, float** arr, float* ans) {
    int i;
    float delta_v;

    for (i = 0; i < array_size; i++) {
        delta_v = (arr[i][1] - arr[i][0]) * 1000 / 3600; 
        ans[i] = delta_v / arr[i][2];  
        
        printf("Row %d | Acceleration = %d\n", i + 1, (int)roundf(ans[i]));
    }
}

void getTxt(const char* filename, float*** arr, unsigned long long* array_size) {
    FILE* ptr = fopen(filename, "r");
    if (ptr == NULL) {
        printf("Error: Could not open file %s. Check if the file exists and the path is correct.\n", filename);
        exit(1);
    }

    if (fscanf_s(ptr, "%llu", array_size) != 1) { 
        printf("Error: Failed to read array size from the file.\n");
        fclose(ptr);
        exit(1);
    }

    printf("File: %s\n", filename);
    printf("Array size: %llu\n", *array_size);

    *arr = (float**)malloc(*array_size * sizeof(float*));
    if (*arr == NULL) {
        printf("Error: Memory allocation failed.\n");
        fclose(ptr);
        exit(1);
    }

    for (unsigned long long i = 0; i < *array_size; i++) {
        (*arr)[i] = (float*)malloc(3 * sizeof(float));
        if ((*arr)[i] == NULL) {
            printf("Error: Memory allocation failed for row %llu.\n", i);
            fclose(ptr);
            exit(1);
        }
    }

    for (unsigned long long i = 0; i < *array_size; i++) {
        if (fscanf_s(ptr, "%f %f %f", &(*arr)[i][0], &(*arr)[i][1], &(*arr)[i][2]) != 3) {
            printf("Error: Incorrect file format or insufficient data.\n");
            fclose(ptr);
            exit(1);
        }
    }

    fclose(ptr);
    printf("Successfully read %llu rows from %s\n", *array_size, filename);
}

void getInput(float*** arr, unsigned long long* array_size) {
    printf("Enter the number of rows: ");
    if (scanf_s("%llu", array_size) != 1) {
        printf("Error: Invalid input.\n");
        exit(1);
    }

    *arr = (float**)malloc(*array_size * sizeof(float*));

    if (*arr == NULL) {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }

    for (unsigned long long i = 0; i < *array_size; i++) {
        (*arr)[i] = (float*)malloc(3 * sizeof(float));
        if ((*arr)[i] == NULL) {
            printf("Error: Memory allocation failed for row %llu.\n", i);
            exit(1);
        }
    }

    printf("Enter the values (vi, vf, t) for each row:\n");
    for (unsigned long long i = 0; i < *array_size; i++) {
        printf("Row %llu: ", i + 1);
        if (scanf_s("%f %f %f", &(*arr)[i][0], &(*arr)[i][1], &(*arr)[i][2]) != 3) {
            printf("Error: Invalid input.\n");
            exit(1);
        }
    }
}

void dispMenu() {
    printf("Choose an option:\n");
    printf("[1] Insert an array\n");
    printf("[2] Read 10.txt\n");
    printf("[3] Read from 100.txt\n");
    printf("[4] Read from 1000.txt\n");
    printf("[5] Read from 10000.txt\n");
    printf("Enter your choice: ");
}

void cmpArr(long long int n, float* c, int* x64) {
    int i;
    int error = 0;

    for (i = 0;i < n;i++) {
        int roundedC = (int)roundf(c[i]);
        printf("Row %d | Original value: %.2f | Rounded value: %d | x64 value: %d\n",
            i + 1, c[i], roundedC, x64[i]);
        if (roundedC != x64[i]) {
            error = 1;
        }
    }

    if (error == 1) {
        printf("Error in checking\n");
    }
    else {
        printf("All values are the same\n");
    }
}

int main() {
    unsigned long long int array_size = 0;
    unsigned long long int array_bytes = 0;
    float** arr = NULL;
    
    clock_t start, end;
    double time_taken;
    int choice;

    dispMenu();
    if (scanf_s("%d", &choice) != 1) {
        printf("Error: Invalid input.\n");
        return 1;
    }

    switch (choice) {
    case 1:
        getInput(&arr, &array_size);
        break;
    case 2:
        getTxt("10.txt", &arr, &array_size);
        break;
    case 3:
        getTxt("100.txt", &arr, &array_size);
        break;
    case 4:
        getTxt("1000.txt", &arr, &array_size);
        break;
    case 5:
        getTxt("10000.txt", &arr, &array_size);
        break;
    default:
        printf("Error\n");
        return 1;
    }

    array_bytes = array_size * 3 * sizeof(float);
    float* ansC = (float*)malloc(array_size * sizeof(float));
    int* ans64 = (int*)malloc(array_size * sizeof(float));

    // first 5 rows check
    /*for (unsigned long long i = 0; i < array_size && i < 5; i++) {
        printf("[Row %llu] vi = %.2f | vf = %.2f | t = %.2f\n", i + 1, arr[i][0], arr[i][1], arr[i][2]);
    }
    */

    start = clock();
    getAcceleration(array_size, arr, ansC);
    end = clock();
    time_taken = ((double)(end - start) * 1000 / CLOCKS_PER_SEC);
    printf("C Time taken: %.2f ms\n", time_taken);

    start = clock();
    x64calc(array_size, arr, ans64);
    end = clock();
    time_taken = ((double)(end - start) * 1000 / CLOCKS_PER_SEC);
    printf("x64 Time taken: %.2f ms\n", time_taken);

    cmpArr(array_size, ansC, ans64);

    free(arr);
    free(ansC);
    return 0;
}
