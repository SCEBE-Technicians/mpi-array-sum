#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#define ARRAY_SIZE 100

double time_diff(struct timeval* start, struct timeval* end) {
    double elapsed_time = (double)(end->tv_sec - start->tv_sec);
    elapsed_time += (double)(end->tv_usec - start->tv_usec) / 1000000;
    return elapsed_time;
}

void fill_array(int *arr) {
    for (int i = 0; i<ARRAY_SIZE; i++) {
        arr[i] = rand();
    }
}

int slow_sum_array(int *arr) {
    int sum = 0;
    for (int i = 0; i<ARRAY_SIZE; i++) {
        sum += arr[i];
        usleep(10000);
    }
    return sum;
}

int main(int argc, char* argv[]) {
    // Seed the rng so every run gives the same result
    srand(0);

    // Create an array of random numbers
    int list_of_random_numbers[ARRAY_SIZE];
    fill_array(list_of_random_numbers);

    // Measure the time before doing the calculation
    struct timeval start;
    struct timeval end;
    gettimeofday(&start, 0);

    int sum = slow_sum_array(list_of_random_numbers);

    // Measure the time after doing the calculation
    gettimeofday(&end, 0);
    double elapsed_time = time_diff(&start, &end);
    
    printf("Sum: %d\n", sum);
    printf("Elapsed time: %f\n", elapsed_time);

    return 0;
}

