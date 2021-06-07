#!/bin/bash

echo "" > log1.txt
echo "" > log2.txt
echo "" > log3.txt
echo "" > log4.txt
echo "" > log5.txt
echo "" > log6.txt
echo "" > log7.txt
echo "" > log8.txt

sh experiment.sh 4 log1.txt &
sh experiment.sh 4 log2.txt &
sh experiment.sh 4 log3.txt &
sh experiment.sh 4 log4.txt &
sh experiment.sh 4 log5.txt &
sh experiment.sh 4 log6.txt &
sh experiment.sh 4 log7.txt &
sh experiment.sh 4 log8.txt &
