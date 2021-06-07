#!/bin/bash

echo -n "" > log.txt
cat log1.txt >> log.txt
cat log2.txt >> log.txt
cat log3.txt >> log.txt
cat log4.txt >> log.txt
cat log5.txt >> log.txt
cat log6.txt >> log.txt
cat log7.txt >> log.txt
cat log8.txt >> log.txt

g++ process.cpp -o process

./process

