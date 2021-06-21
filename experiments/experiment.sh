#!/bin/bash

execute_all(){
#dir="../instances/set_1_2"
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
}

execute_instance(){
    file="../instances/set_4_4/p4.4.t.txt"
    echo "$file" >> $2
    ./../Project/TOP_GRASP_TS_PR 1 1 1 $file --alpha 0.86 --iterations 3540 --path y >> $2
}

execute_all $1 $2
