# Parallelized Matrix Multiplication using OpenMP
**Student:** Pablo Agustín Ortega Kral - A00344664

The objective of this lab was to a code in C that multiplies two matrixes of any size, provided these can be multiplied, and then use **OpenMP** to parallelize this operation. OpenMP is an API for shared-memory parallel programming in C and C++ .

To validate the given approach, the code was tested for a small operation whose result was known.

$$ {\left\lbrack \matrix{2 & 3 \cr 4 & 5} \right\rbrack} 
* \left\lbrack \matrix{1 & 0 \cr 0 & 1} \right\rbrack
= \left\lbrack \matrix{2 & 3 \cr 4 & 5} \right\rbrack
$$

To compile this project run the **make** command. The binary can be erased by running **make clean**. The compiled binary takes as arguments the number of threads, the size of the square test matrixes and a flag that indicates if the result wishes to be printed or not.
For instance, the following example multiplies two 300x300 matrixes using 8 threads. An printing the result.
```
./MatMul 8 300 1
```

# Performance testing
To test this approach a function was written to generate random matrixes given a size.

The code was tested for 300X300 matrixes using 1 to 16 threads, 34 threads were also used to test what will happen if the number of virtual cores of a CPU is exceeded. An average of 8 executions was taken for a more indicative result.
## Time vs Threads
![Time](figures/)

## CPU Usage
To verify that the threads are indeed running in separate cores we can use a system monitoring tool such as **htop** to verify the CPU usage. By doing this, we can see that the load gets distributed between different cores.
![usage-1thread](figures/1T-use.png?raw=true "Usage 1 Thread")

![usage-20threads](figures/20T-use.png?raw=true "Usage 20 Threads")

![usage-systemMonitor](figures/SysMonitor.png?raw=true "System Monitor")

# Conclusion
