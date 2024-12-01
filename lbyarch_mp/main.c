#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
        float fractional_part = c[i] - floorf(c[i]);  //fractional part of c[i]

        if (fractional_part == 0.5f) {
            roundedC = (int)(roundf(c[i] / 2) * 2);
        }
        else {
            roundedC = (int)roundf(c[i]);
        }

        printf("Row %d | Original value: %.2f | Rounded value: %d | x64 value: %d\n",
            i + 1, c[i], roundedC, x64[i]);

        if (roundedC != x64[i]) {
            error = 1;
        }
    }

    if (error == 1) {
        printf("Values do not match\n");
    }
    else {
        printf("All values are the same\n");
    }
}

void getTxt(const char* filename) {
    unsigned long long int array_size;
    FILE* ptr = fopen(filename, "r");
    if (ptr == NULL) {
        printf("Error: Could not open file %s. Check if the file exists and the path is correct.\n", filename);
        exit(1);
    }

    if (fscanf_s(ptr, "%llu", &array_size) != 1) { 
        printf("Error: Failed to read array size from the file.\n");
        fclose(ptr);
        exit(1);
    }

    printf("File: %s\n", filename);
    printf("Array size: %llu\n", array_size);

    float (*arr)[3] = malloc(array_size * 3 * sizeof(float));
    if (*arr == NULL) {
        printf("Error: Memory allocation failed.\n");
        fclose(ptr);
        exit(1);
    }

    for (unsigned long long i = 0; i < array_size; i++) {
        //arr[i] = (float*)malloc(3 * sizeof(float));
        if (arr[i] == NULL) {
            printf("Error: Memory allocation failed for row %llu.\n", i);
            fclose(ptr);
            exit(1);
        }
    }

    for (unsigned long long i = 0; i < array_size; i++) {
        if (fscanf_s(ptr, "%f %f %f", &arr[i][0], &arr[i][1], &arr[i][2]) != 3) {
            printf("Error: Incorrect file format or insufficient data.\n");
            fclose(ptr);
            exit(1);
        }
    }

    fclose(ptr);
    printf("Successfully read %llu rows from %s\n", array_size, filename);


    float* ansC = (float*)malloc(array_size * sizeof(float));
    int* ans64 = (int*)malloc(array_size * sizeof(float));
    clock_t start, end;
    double time_taken, c_total, c_avg, x_total, x_avg;
    double total_time = 0.0;

    for (int i = 0; i < 30; i++) {
        start = clock();
        getAcceleration(array_size, arr, ansC);
        end = clock();
        time_taken = ((double)(end - start) * 1000 / CLOCKS_PER_SEC);
        total_time += time_taken;
    }
    c_total = total_time;
    c_avg = total_time / 30;

    total_time = 0.0; //reset

    for (int i = 0; i < 30; i++) {
        start = clock();
        x64calc(array_size, arr, ans64);
        end = clock();
        time_taken = ((double)(end - start) * 1000 / CLOCKS_PER_SEC);
        total_time += time_taken;
    }
    x_total = total_time;
    x_avg = total_time / 30;

    printf("\n----------------------------------------\n");
    printf("\nRESULTS \n");
    printf("Number of rows: %llu\n", array_size);
    printf("Correctness check: \n");
    cmpArr(array_size, ansC, ans64);

    printf("\nC Performance\n");
    printf("Average time taken (30 runs): %.2f ms\n", c_avg);
    printf("Total time taken   (30 runs): %.2f ms\n", c_total);

    printf("\nx86-64 Performance\n");
    printf("Average time taken (30 runs): %.2f ms\n", x_avg);
    printf("Total time taken   (30 runs): %.2f ms\n", x_total);

    printf("\n----------------------------------------\n");
}

void getInput() {
    unsigned long long int array_size;
    printf("Enter the number of rows: ");
    if (scanf_s("%llu", &array_size) != 1) {
        printf("Error: Invalid input.\n");
        exit(1);
    }

    float (*arr)[3] = malloc(array_size * 3 * sizeof(float));

    if (*arr == NULL) {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }

    for (unsigned long long i = 0; i < array_size; i++) {
        //(*arr)[i] = (float*)malloc(3 * sizeof(float));
        if (arr[i] == NULL) {
            printf("Error: Memory allocation failed for row %llu.\n", i);
            exit(1);
        }
    }

    printf("Enter the values (vi vf t) for each row:\n");
    for (unsigned long long i = 0; i < array_size; i++) {
        printf("Row %llu: ", i + 1);
        if (scanf_s("%f %f %f", &arr[i][0], &arr[i][1], &arr[i][2]) != 3) {
            printf("Error: Invalid input.\n");
            exit(1);
        }
    }

    float* ansC = (float*)malloc(array_size * sizeof(float));
    int* ans64 = (int*)malloc(array_size * sizeof(float));
    clock_t start, end;
    double time_taken, c_total, c_avg, x_total, x_avg;
    double total_time = 0.0;

    for (int i = 0; i < 30; i++) {
        start = clock();
        getAcceleration(array_size, arr, ansC);
        end = clock();
        time_taken = ((double)(end - start) * 1000 / CLOCKS_PER_SEC);
        total_time += time_taken;
    }
    c_total = total_time;
    c_avg = total_time / 30;

    total_time = 0.0; //reset

    for (int i = 0; i < 30; i++) {
        start = clock();
        x64calc(array_size, arr, ans64);
        end = clock();
        time_taken = ((double)(end - start) * 1000 / CLOCKS_PER_SEC);
        total_time += time_taken;
    }
    x_total = total_time;
    x_avg = total_time / 30;

    printf("\n----------------------------------------\n");
    printf("\nRESULTS \n");
    printf("Number of rows: %llu\n", array_size);
    printf("Correctness check: \n");
    cmpArr(array_size, ansC, ans64);

    printf("\nC Performance\n");
    printf("Average time taken (30 runs): %.2f ms\n", c_avg);
    printf("Total time taken   (30 runs): %.2f ms\n", c_total);

    printf("\nx86-64 Performance\n");
    printf("Average time taken (30 runs): %.2f ms\n", x_avg);
    printf("Total time taken   (30 runs): %.2f ms\n", x_total);

    printf("\n----------------------------------------\n");
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



int main() {
    //unsigned long long int array_size = 0;
    //unsigned long long int array_bytes = 0;
    //float (*arr)[3];
    
    /*clock_t start, end;
    double time_taken, c_total, c_avg, x_total, x_avg;
    double total_time = 0.0;*/
    int choice;

    dispMenu();
    if (scanf_s("%d", &choice) != 1) {
        printf("Error: Invalid input.\n");
        return 1;
    }

    switch (choice) {
    case 1:
        getInput();
        break;
    case 2:
        getTxt("10.txt");
        break;
    case 3:
        getTxt("100.txt");
        break;
    case 4:
        getTxt("1000.txt");
        break;
    case 5:
        getTxt("10000.txt");
        break;
    default:
        printf("Error\n");
        return 1;
    }
    
    //array_bytes = array_size * 3 * sizeof(float);
    /*float* ansC = (float*)malloc(array_size * sizeof(float));
    int* ans64 = (int*)malloc(array_size * sizeof(float));*/

    // first 5 rows check
    /*for (unsigned long long i = 0; i < array_size && i < 5; i++) {
        printf("[Row %llu] vi = %.2f | vf = %.2f | t = %.2f\n", i + 1, arr[i][0], arr[i][1], arr[i][2]);
    }
    */
    //float arr[][3] = { {0.0, 62.5, 10.1}, {60.0, 122.3, 5.5},{30.0, 160.7, 7.8} };

    /*for (int i = 0; i < 30; i++) {
        start = clock();
        getAcceleration(array_size, arr, ansC);
        end = clock();
        time_taken = ((double)(end - start) * 1000 / CLOCKS_PER_SEC);
        total_time += time_taken;
    }
    c_total= total_time;
    c_avg = total_time/30;

    total_time = 0.0; //reset

    for (int i = 0; i < 30; i++) {
        start = clock();
        x64calc(array_size, arr, ans64);
        end = clock();
        time_taken = ((double)(end - start) * 1000 / CLOCKS_PER_SEC);
        total_time += time_taken;
    }
    x_total= total_time;
    x_avg =total_time / 30;
    
    printf("\n----------------------------------------\n");
    printf("\nRESULTS \n");
    printf("Number of rows: %llu\n", array_size);
    printf("Correctness check: \n");
    cmpArr(array_size, ansC, ans64);

    printf("\nC Performance\n");
    printf("Average time taken (30 runs): %.2f ms\n", c_avg);
    printf("Total time taken   (30 runs): %.2f ms\n", c_total);

    printf("\nx86-64 Performance\n");
    printf("Average time taken (30 runs): %.2f ms\n", x_avg);
    printf("Total time taken   (30 runs): %.2f ms\n", x_total);

    printf("\n----------------------------------------\n");*/
    
    //free(arr);
    //free(ansC);

    return 0;
}
