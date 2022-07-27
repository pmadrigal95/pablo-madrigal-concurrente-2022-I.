#!/bin/bash
#SBATCH --job-name=tetris_solver_mpi
#SBATCH --output=result.txt
#SBATCH --partition=nu-wide
#SBATCH --ntasks=3
#SBATCH --nodes=3
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:05:00

module load gcc /7.2.0
module load mpich /3.2.1-gcc-7.2.0

mpiexec -np 3 ./bin/tetris_solver_mpi "/home/curso-658/tetris_solver_mpi/tetris_solver_mpi/test/test01.txt" 9
