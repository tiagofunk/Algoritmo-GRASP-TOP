#!/bin/bash

for file in ../instances/set_1_2/*
do
    if [ -f "$file" ]
    then
        echo "$file"
        ./../Project/TOP_GRASP_TS_PR 1234 1.0 $file
    fi
done
