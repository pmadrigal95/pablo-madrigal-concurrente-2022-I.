#!/bin/bash
#SBATCH --job-name=tetris_solver_mpi
#SBATCH --output=result.txt
#SBATCH --partition=nu-wide
#SBATCH --ntasks=2
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:05:00

module load gcc /7.2.0
module load mpich /3.2.1-gcc-7.2.0

mpiexec -np 2 ../bin/tetris_solver_mpi
