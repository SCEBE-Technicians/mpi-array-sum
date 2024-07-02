#!/bin/sh
#SBATCH --export=ALL
#SBATCH --nodes 1
#SBATCH --ntasks=4
#SBATCH --partition gpu
#SBATCH --output parallel.results

mpirun -n 4 par
