#!/bin/bash

dir=./version_03
repetions=4

echo -n "" > "$dir/log1".txt
echo -n "" > "$dir/log2".txt
echo -n "" > "$dir/log3".txt
echo -n "" > "$dir/log4".txt
echo -n "" > "$dir/log5".txt
echo -n "" > "$dir/log6".txt
echo -n "" > "$dir/log7".txt
echo -n "" > "$dir/log8".txt

sh experiment.sh $repetions "$dir/log1".txt &
sh experiment.sh $repetions "$dir/log2".txt &
sh experiment.sh $repetions "$dir/log3".txt &
sh experiment.sh $repetions "$dir/log4".txt &
sh experiment.sh $repetions "$dir/log5".txt &
sh experiment.sh $repetions "$dir/log6".txt &
sh experiment.sh $repetions "$dir/log7".txt &
sh experiment.sh $repetions "$dir/log8".txt &
