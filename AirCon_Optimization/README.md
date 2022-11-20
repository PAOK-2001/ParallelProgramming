# Optimization of air condition system in an industrial unit.
_Pablo Agustín Ortega Kral A00344664_

## Approach
The following code simulates a distributed system approach to traverse a room and measure the temperature in given zones. To do this, we read a room layout from a CSV file that contains a temperature distribution in terms of hot (H) and cold (C). After loading the layout we traverse the room with N number of threads which symbolize the number of robots, the robots give hot zones a temperature between 60° to 100° and cold zones values from 0° to 60°; there is a master thread (in this case we use the main function) which checks if the whole the room has been covered to cancel the execution of the robots when this happens. A delay was introduced to simulate the sample and traversal time of the robots, this also allows us to visualize the speedup of having multiple robots(threads) sensing the room.

After this, we use a discretized form of the differential heat equation to estimate the temperature of the room after 10 hours. Since this involves iterating through a tridimensional matrix _u(time, x, y)_ OpenMP is used to distribute the load. _#pragma parallel for_ is used to parallelize the loops between the threads.

## Results
## Sensed temperature by robots
We can see the given temperatures follow the provided distribution. With hot zones in the middle and cold zones on the sides.

![HeathMap0](figures/heatmp0.png?raw=true "Heat map T=0")
## Predicted temperature 
We can see that the heat equation makes sense as the room cools down and the temperature begins to normalize. The cool zones become warmer and the hot zones cool down.

![HeatMap10](figures/heatmp10.png?raw=true "Heat map T=10")

## Tests and performance
![Performance](figures/exection_graph.png?raw=true "Heat map T=10")

![CPU-Use](figures/CPU-Usage.png?raw=true "Heat map T=10")
## Conclusion

Parallel programming allows us to run block of code simultaneously by distributing their load on different cores of the CPU. The type of parallel programming shown here is shared memory (though the simulated scenario is distributed memory) and we are also showcasing two approaches for parallelizing shared memory problems:
- _pthreads_: allows us to manually create and control the threads to run the code. Here we point the created threads to the functions we want them to run. We can group threads together using pthread_join. And to handle race conditions we use mutual exclusion.
- _OpenMP_: intead about worrying about individual threads, we instead chose the blocks of code we want to run in parallel and specify how the variables relate to problem using the private and global scope, the API then takes care of the rest for us.

Finally, as showed in the performance graph, we can see that parallel programming is a powerful tool to optimize runtime with demanding load. However, we can see that it is by no means _"free performance"_ as it comes at the cost of resource uses and as the number of threads increments we get diminishing returns as the hardware becomes our bottleneck.