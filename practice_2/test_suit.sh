#!/bin/bash
# Basic while loop
counter=1
while [ $counter -le $1 ]
do
echo Running with $counter threads
time ./MatMul $counter 300 0
echo " "
((counter++))
done