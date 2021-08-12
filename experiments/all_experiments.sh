#!/bin/bash

dir=./version_02

echo -n "" > "$dir/log1".txt
echo -n "" > "$dir/log2".txt
echo -n "" > "$dir/log3".txt
echo -n "" > "$dir/log4".txt
echo -n "" > "$dir/log5".txt
echo -n "" > "$dir/log6".txt
echo -n "" > "$dir/log7".txt
echo -n "" > "$dir/log8".txt

sh experiment.sh 4 "$dir/log1".txt &
sh experiment.sh 4 "$dir/log2".txt &
sh experiment.sh 4 "$dir/log3".txt &
sh experiment.sh 4 "$dir/log4".txt &
sh experiment.sh 4 "$dir/log5".txt &
sh experiment.sh 4 "$dir/log6".txt &
sh experiment.sh 4 "$dir/log7".txt &
sh experiment.sh 4 "$dir/log8".txt &
