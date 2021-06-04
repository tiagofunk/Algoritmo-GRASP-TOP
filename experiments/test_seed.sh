#!/bin/bash

#echo "instance,strategy,result,time" > $log
for seed in $(seq 1 1000)
do
    #for alpha in $(seq 1 10)
    #do
	#aux = $alpha/10
	echo "$seed"
        ./../Project/TOP_GRASP_TS_PR $seed 1.0 ../Project/a.txt #$aux ../Project/a.txt
   # done
done
