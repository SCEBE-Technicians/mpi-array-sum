#!/bin/sh
#SBATCH --export=ALL
#SBATCH --nodes 1
#SBATCH --ntasks=1
#SBATCH --partition himem
#SBATCH --output results/serial.out

make serial > /dev/null
./serial
