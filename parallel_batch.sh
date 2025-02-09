#!/bin/sh
#SBATCH --export=ALL
#SBATCH --nodes 1
#SBATCH --ntasks=10
#SBATCH --partition gpu
#SBATCH --output results/parallel.out

make parallel > /dev/null
# Number of processes must divide 100
mpirun -n 10 parallel
