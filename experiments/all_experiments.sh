#!/bin/bash

echo -n "" > log1.txt
echo -n "" > log2.txt
echo -n "" > log3.txt
echo -n "" > log4.txt
echo -n "" > log5.txt
echo -n "" > log6.txt
echo -n "" > log7.txt
echo -n "" > log8.txt

sh experiment.sh 4 log1.txt &
sh experiment.sh 4 log2.txt &
sh experiment.sh 4 log3.txt &
sh experiment.sh 4 log4.txt &
sh experiment.sh 4 log5.txt &
sh experiment.sh 4 log6.txt &
sh experiment.sh 4 log7.txt &
sh experiment.sh 4 log8.txt &
