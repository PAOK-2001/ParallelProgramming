# Montecarlo Method for estimating Pi: Using threads.
**Student:** Pablo Agustín Ortega Kral - A00344664

The objective of this lab was to a code in C that multiplies two matrixes of any size, provided these can be multiplied, and then use **OpenMP** to parallelize this operation. OpenMP is an API for shared-memory parallel programming in C and C++ . 

To compile this project run the **make** command. The binary can be erased by running **make clean**. The compiled binary takes as arguments the number of threads, the size of the square test matrixes and a flag that indicates if the result wishes to be printed or not.
Example.

# Performance testing
The code was tested for 10,000,000 using 1 thread, 2 threads, 4 threads, 8 threads, and 16 threads. An average of 8 executions was taken.
## Time vs Threads
![Time](figures/Average%20time%20vs%20Number%20of%20Threads.png?raw=true "Test1")

## CPU Usage
To verify that the threads are indeed running in separate cores we can use a system monitoring tool such as **htop** to verify the CPU usage. By doing this, we can see that the load gets distributed between different cores.
![usage-1thread](figures/1T-use.png?raw=true "Usage 1 Thread")

![usage-20threads](figures/20T-use.png?raw=true "Usage 20 Threads")

![usage-systemMonitor](figures/SysMonitor.png?raw=true "System Monitor")

# Conclusion
This lab showed how to distribute the load of a process into different threads. To create threads in C using _pthreads_ we must define a variable in memory where the thread will live and then we must specify which function will run in the given thread. Something crucial is how to manage the implemented threads; some processes (like the one implemented here) require all threads to finish at the same time before continuing with the main thread, for this we can use the pthreads_join function. Another important consideration is how said threads will interact with global variables; to avoid threads "fighting" for variables we can use a _mutex_ (Mutual Exclusion) that "blocks" a variable from being used while another thread is accessing it.

While implementing threads can yield significant performance gains for certain applications, it greatly depends on the nature of the problem. In some instances the toll of diving the problem is grater than the benefits of running the computations in parallel.

