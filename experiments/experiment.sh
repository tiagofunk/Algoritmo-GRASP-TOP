#!/bin/bash

execute_all(){
    for file in $3/*
    do
        if [ -f "$file" ]
        then
            for n in $(seq 1 $1)
            do
                echo "$n-$file"
                echo "$file" >> $2
                ./../Project/TOP_GRASP_TS_PR 1 1 1 $file --alpha 0.9 --iterations 4500 --path y --margin 1.9 --removeOperator r --removePercentage 0.15 --shuffleOperator e --addOperator b >> $2
            done
        fi
    done
}

n=$1
log=$2
dir=$3

echo $n
echo $log
echo $dir

execute_all $n $log $dir
