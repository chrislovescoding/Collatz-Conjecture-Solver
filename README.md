# Collatz Conjecture Solver

A console application written in C++ that performs a variety of tasks based on the Collatz conjecture (3x+1 problem). This tool can also visualize the progression of numbers using a graph.

## Description

The program can perform the following tasks:

1. Check if the Collatz conjecture holds true for all numbers up to a user-defined limit.
2. Verify the conjecture for a single, arbitrarily large number.
3. Test the conjecture for a range of numbers, starting from a user-defined point.
4. A special test using numbers derived from a base and an exponent.

## Dependencies

- C++ (with support for the GMP library)
- Python (for graph visualization)
- [matplotlib](https://matplotlib.org/) (for graph plotting in Python)

## Usage

Compile the C++ code with:
g++ 3x+1.cpp -o 3x+1.exe -lgmp -lgmpxx -Wall -Wextra -g3 -fopenmp -O2


Run the executable and follow the on-screen instructions.

For visualizing the sequence, the `3x+1graphvisualiser.py` script will be automatically executed by the C++ program. When prompted, you can decide whether to apply logarithmic scaling to the y-axis.

## Future Improvements

1. **Parallelization with TBB**: The current version uses OpenMP for parallelism. In future implementations, we consider switching to TBB (Threading Building Blocks) to potentially decrease the overhead from creating threads and improve performance.

2. **Hash Table**: Implementing a hash table to store numbers that have already been verified to converge to 1 will save unnecessary recalculations, further optimizing the program.

## Credits

Written by Christopher Lock
