#!/bin/bash

echo "Starting L-SHADE analysis..."
echo ""

echo "Processing linear_congruential data..."
./build/main ../data/linear_congruential.csv > results/linear_congruential.csv
echo "  - linear_congruential.csv (default)"
./build/main ../data/linear_congruential.csv 1000000 > results/linear_congruential_1M.csv
echo "  - linear_congruential_1M.csv (1000000)"
./build/main ../data/linear_congruential.csv 100000 > results/linear_congruential_100K.csv
echo "  - linear_congruential_100K.csv (100000)"
./build/main ../data/linear_congruential.csv 10000 > results/linear_congruential_10K.csv
echo "  - linear_congruential_10K.csv (10000)"
./build/main ../data/linear_congruential.csv 1000 > results/linear_congruential_1K.csv
echo "  - linear_congruential_1K.csv (1000)"
./build/main ../data/linear_congruential.csv 100 > results/linear_congruential_100.csv
echo "  - linear_congruential_100.csv (100)"
echo ""

echo "Processing mersenne_twister data..."
./build/main ../data/mersenne_twister.csv > results/mersenne_twister.csv
echo "  - mersenne_twister.csv (default)"
./build/main ../data/mersenne_twister.csv 1000000 > results/mersenne_twister_1M.csv
echo "  - mersenne_twister_1M.csv (1000000)"
./build/main ../data/mersenne_twister.csv 100000 > results/mersenne_twister_100K.csv
echo "  - mersenne_twister_100K.csv (100000)"
./build/main ../data/mersenne_twister.csv 10000 > results/mersenne_twister_10K.csv
echo "  - mersenne_twister_10K.csv (10000)"
./build/main ../data/mersenne_twister.csv 1000 > results/mersenne_twister_1K.csv
echo "  - mersenne_twister_1K.csv (1000)"
./build/main ../data/mersenne_twister.csv 100 > results/mersenne_twister_100.csv
echo "  - mersenne_twister_100.csv (100)"
echo ""

echo "Processing true_random data..."
./build/main ../data/true_random.csv > results/true_random.csv
echo "  - true_random.csv (default)"
./build/main ../data/true_random.csv 1000000 > results/true_random_1M.csv
echo "  - true_random_1M.csv (1000000)"
./build/main ../data/true_random.csv 100000 > results/true_random_100K.csv
echo "  - true_random_100K.csv (100000)"
./build/main ../data/true_random.csv 10000 > results/true_random_10K.csv
echo "  - true_random_10K.csv (10000)"
./build/main ../data/true_random.csv 1000 > results/true_random_1K.csv
echo "  - true_random_1K.csv (1000)"
./build/main ../data/true_random.csv 100 > results/true_random_100.csv
echo "  - true_random_100.csv (100)"
echo ""

echo "All processing complete!"
