# Acceleration Calculator
LBYARCH MP by: Go, Jeanne Frances & Loria, Andrea Euceli (S12)

## Analysis

| |C Avg. Time Taken (in microseconds) |x86-64 Avg. Time Taken (in microseconds)|
| ------------- | ------------- | ------------- |
Manual Input | 0.05 | 0.04
10.txt | 0.10 | 0.05
100.txt | 0.40 | 0.21
1000.txt | 4.12 | 1.90
10000.txt | 37.84 | 18.78

![graph](https://github.com/user-attachments/assets/ea5c611f-e802-4203-aeae-2d5e92f3e731)

In order to obtain accurate results in executing the assembly function, Query Performance Counter was utilized to acquire the execution time in microseconds, and the average time was calculated by running the function 30 times. As seen from the average time taken in the table above, it is clear that assembly execution in calculating is a consistently faster than the C execution. This is especially true with larger inputs where assembly nearly halves the time taken by C. This shows that assembly programs are generally faster than C programs and more efficient for processing larger datasets.

## Output
### Manual input
Number of rows: 3
| | C | x86-64 |
| ------------- | ------------- | ------------- |
Average Time Taken | 0.05 | 0.04
Total Time Taken | 1.40 | 1.20

![Manual input results](https://github.com/user-attachments/assets/caeb6cd0-d353-4a63-8929-0d7f39cc0a9b)

### 10.txt
Number of rows: 10
| | C | x86-64 |
| ------------- | ------------- | ------------- |
Average Time Taken | 0.10 | 0.05
Total Time Taken | 2.90 | 1.50

![10.txt results](https://github.com/user-attachments/assets/31709683-cb4f-4f04-ba52-f0a98251459f)

### 100.txt
Number of rows: 100
| | C | x86-64 |
| ------------- | ------------- | ------------- |
Average Time Taken | 0.40 | 0.21
Total Time Taken | 12.10 | 6.40

![100.txt results](https://github.com/user-attachments/assets/8dce7d02-b9a8-4df6-be88-7603881fbade)

### 1000.txt
Number of rows: 1000
| | C | x86-64 |
| ------------- | ------------- | ------------- |
Average Time Taken | 4.12 | 1.90
Total Time Taken | 123.60 | 57.10

![1000.txt results](https://github.com/user-attachments/assets/9673b534-4757-4ea4-b6e1-3310b0114e10)

### 10000.txt
Number of rows: 10000
| | C | x86-64 |
| ------------- | ------------- | ------------- |
Average Time Taken | 37.84 | 18.78
Total Time Taken | 1135.20 | 563.30

![10000.txt results](https://github.com/user-attachments/assets/74d0ff2a-59e2-439c-aa1f-17e54a971eba)

## Short Video
[![Watch the video](https://img.youtube.com/vi/yyt7ls6oqsc/0.jpg)](https://www.youtube.com/watch?v=yyt7ls6oqsc)

https://www.youtube.com/watch?v=yyt7ls6oqsc
