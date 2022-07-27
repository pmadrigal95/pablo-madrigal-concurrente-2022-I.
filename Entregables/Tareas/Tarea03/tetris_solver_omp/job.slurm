#!/bin/bash
#SBATCH --job-name=tetris_solver_omp
#SBATCH --output=result.txt
#SBATCH --partition=nu-wide
#SBATCH --ntasks=1
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:05:00

module load gcc /7.2.0
module load mpich /3.2.1-gcc-7.2.0

mpiexec -np 1 ./bin/tetris_solver_omp "/home/curso-658/tetris_solver_omp/tetris_solver_omp/test/test01.txt" 9
