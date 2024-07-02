all: serial parallel parallel_reduce

serial: serial_array_sum.c
	gcc serial_array_sum.c -o serial

parallel: parallel_array_sum.c
	mpicc parallel_array_sum.c -o parallel

parallel_reduce: parallel_array_sum_with_reduce.c
	mpicc parallel_array_sum_with_reduce.c -o parallel_reduce

clean:
	rm serial parallel parallel_reduce
