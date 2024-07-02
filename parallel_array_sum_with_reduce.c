#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <mpi.h>

#define ARRAY_SIZE 100

void mpi_setup(int *world_size, int *rank) {
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, rank);
    MPI_Comm_size(MPI_COMM_WORLD, world_size);
}

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

int slow_sum_array(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i<size; i++) {
        sum += arr[i];
        usleep(10000);
    }
    return sum;
}

int main(int argc, char* argv[]) {
    int rank, world_size;
    mpi_setup(&world_size, &rank);
    
    // Create an array of random numbers
    int list_of_random_numbers[ARRAY_SIZE];
    fill_array(list_of_random_numbers);

    long sum = 0;
    
    // Measure the time before doing the calculation
    struct timeval start;
    struct timeval end;
    if (rank == 0) {
        gettimeofday(&start, 0);
    }

    int elements_per_proc = ARRAY_SIZE/world_size;
    int *sub_array = malloc(sizeof(int) * elements_per_proc);

    MPI_Scatter(list_of_random_numbers, elements_per_proc, MPI_INT, sub_array, elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);

    sum = slow_sum_array(sub_array, elements_per_proc);

    int *sub_sums;
    if (rank == 0) {
        sub_sums = (int *)malloc(sizeof(float) * world_size);
    }

    int aggregate_sum = 0;
    MPI_Reduce(&sum, &aggregate_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Measure the time after doing the calculation
    if (rank == 0) {
        gettimeofday(&end, 0);
        double elapsed_time = time_diff(&start, &end);
        free(sub_sums);
        printf("Sum: %d\n", aggregate_sum);
        printf("Elapsed time: %f\n", elapsed_time);
    }

    MPI_Finalize();
}
