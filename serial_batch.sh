#!/bin/sh
#SBATCH --export=ALL
#SBATCH --nodes 1
#SBATCH --ntasks=1
#SBATCH --partition gpu
#SBATCH --output serial.results

./sum
