# Montecarlo Method for estimating Pi: Using threads.
Pablo Agustín Ortega Kral - A00344664

The objective of this lab was to develop a code in C that estimates pi using the Montecarlo Method with a N number of threads. The Montecarlo Method for calculating Pi uses the ration between the area of a square and the circle that fits inside this corresponding square; to calculate this area numerically we can "fill" the square with pixels and determine which one of these lie within the circle.

To divide this task into threads the function **montecarlo_chunks** was defined, which takes as an argument the number of threads and divides the number of pixels placed by the number of threads.

To compile this project run the **make** command. The binary can be erased by running **make clean**
# Performance testing
The code was tested for 10,000,000 using 1 thread, 2 threads, 4 threads, 8 threads, and 16 threads. An average of 8 executions was taken.
## Time vs Threads

## CPU Usage


# Conclusion
This lab was meant to show how to optimize process using threads; however the results showed that performance was actually worse.