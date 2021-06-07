#!/bin/bash

for dir in ../instances/*
do
    for file in $dir/*
    do
        if [ -f "$file" ]
        then
            for n in $(seq 1 $1)
            do
                echo "$n-$file"
                echo "$file" >> $2
                ./../Project/TOP_GRASP_TS_PR 1 1 1 $file --alpha 0.86 --iterations 3540 --path y >> $2
            done
        fi
    done
done