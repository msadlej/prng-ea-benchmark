#!/bin/bash -l
#SBATCH -J L-SHADE
#SBATCH -N 1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=19
#SBATCH --mem-per-cpu=4GB
#SBATCH --time=24:00:00
#SBATCH -A plgcmaes
#SBATCH -p plgrid
#SBATCH --output="output.out"
#SBATCH --error="error.err"

cd $SLURM_SUBMIT_DIR
mkdir -p results

MAX_JOBS=$SLURM_CPUS_PER_TASK
METHOD="linear_congruential"
DIM="50_dim"

echo "Starting L-SHADE analysis with $MAX_JOBS parallel jobs..."
echo ""

echo "Processing unlimited data..."
./build/main > "results/$DIM/$METHOD/unlimited.csv"
echo ""

echo "Processing shuffle data..."
./build/main 10000000 shuffle > "results/$DIM/$METHOD/shuffle_10M.csv"
./build/main 1000000 shuffle > "results/$DIM/$METHOD/shuffle_1M.csv"
./build/main 100000 shuffle > "results/$DIM/$METHOD/shuffle_100K.csv"
./build/main 10000 shuffle > "results/$DIM/$METHOD/shuffle_10K.csv"
./build/main 1000 shuffle > "results/$DIM/$METHOD/shuffle_1K.csv"
echo ""

echo "Processing offset data..."
./build/main 10000000 offset > "results/$DIM/$METHOD/offset_10M.csv"
./build/main 1000000 offset > "results/$DIM/$METHOD/offset_1M.csv"
./build/main 100000 offset > "results/$DIM/$METHOD/offset_100K.csv"
./build/main 10000 offset > "results/$DIM/$METHOD/offset_10K.csv"
./build/main 1000 offset > "results/$DIM/$METHOD/offset_1K.csv"
echo ""

echo "Processing restart data..."
./build/main 10000000 > "results/$DIM/$METHOD/restart_10M.csv"
./build/main 1000000 > "results/$DIM/$METHOD/restart_1M.csv"
./build/main 100000 > "results/$DIM/$METHOD/restart_100K.csv"
./build/main 10000 > "results/$DIM/$METHOD/restart_10K.csv"
./build/main 1000 > "results/$DIM/$METHOD/restart_1K.csv"
echo ""

echo "All processing complete!"
