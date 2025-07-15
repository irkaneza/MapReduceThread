# Simplified MapReduce in C++
This project implements a simplified version of the popular MapReduce concept using C++ threads. The aim is to process sequences in parallel by applying a unary functor to elements of the sequence, followed by combining the results using a binary functor, all while dividing the work into multiple threads for concurrent execution.

The solution leverages std::thread to handle thread management and allows for efficient processing without altering or copying the input sequence. Additionally, no synchronization primitives are used, as there are no shared mutable data between threads.

# Problem Statement
The task is to implement a function map_reduce that takes the following inputs:

- An iterator to the beginning of a sequence
- An iterator to the end of a sequence
- A unary functor that can be applied to elements of the sequence
- A binary functor that combines the results of applying the unary functor
- The number of threads to use for parallel processing
