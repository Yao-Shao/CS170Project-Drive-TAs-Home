# Why our alg works well?

## Randomized

-  Simulated annealing is good to approximate global optimization in a large search space for an optimization problem. By accepting worse solutions, we are less likely to get stuck at the local minima and it allow an extensive search power for global optimal.  Besides, we can also control the running time for our alg by just adjusting the hyper-params in SA, such as the maximal iterations and initial temperature.

- Also, it may be very hard to design a deterministic alg with a low approximation ratio since We have proved that Drive TA Home is an NP hard problem. In contrast, a randomized alg gives us the opportunity to keep updating the current best solution by just generating new solutions. Since we have a relatively long computing time, we can write a script to do this automatically until we run out of time. 

## Further Optimization

- We didn't stop at the simulated annealing, we further optimized our solution by rearranging the drop-off locations by analyzing every three adjacent vertices in the circle. This can be done very efficiently and could give us a better solution.