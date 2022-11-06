#!/bin/bash
counter=$1
while [ $counter -le $2 ]
do
echo Running with $counter threads
time ./MatMul $counter $3 0
echo " "
((counter=counter + 1))
done