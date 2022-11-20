# Optimization of air condition system in an industrial unit.
_Pablo Agustín Ortega Kral A00344664_

## Approach
The following code simulates a distributed system approach to traverse a room and measure the temperature in given zones. To do this, we read a room layout from a CSV file that contains a temperature distribution in terms of hot (H) and cold (C). After loading the layout we traverse the room with N number of threads which symbolize the number of robots, the robots give hot zones a temperature between 60° to 100° and cold zones values from 0° to 60°; there is a master thread (in this case we use the main function) which checks if the whole the room has been covered to cancel the execution of the robots when this happens. A delay was introduced to simulate the sample and traversal time of the robots, this also allows us to visualize the speedup of having multiple robots(threads) sensing the room.

After this, we use a discretized form of the differential heat equation to estimate the temperature of the room after 10 hours. Since this involves iterating through a tridimensional matrix _u(time, x, y)_ OpenMP is used to distribute the load. _#pragma parallel for_ is used to parallelize the loops between the threads.

## Results
## Sensed temperature by robots
We can see the given temperatures follow the provided distribution. With hot zones in the middle and cold zones on the sides.
![HeathMap0](figures/heatmp0.png?raw=true "Usage 1 Thread")
## Predicted temperature 
We can see that the heat equation makes sense as the room cools down and the temperature begins to normalize. The cool zones become warmer and the hot zones cool down.
![HeathMap10](figures/heatmp10.png?raw=true "Usage 1 Thread")

## Test and performance

## Conclusion