#!/bin/bash

dir=./version_02/

write_on_log_txt(){
    cat $1 >> log.txt
    echo "" >> log.txt
}

cd $dir

echo -n "" > log.txt

write_on_log_txt log1.txt
write_on_log_txt log2.txt
write_on_log_txt log3.txt
write_on_log_txt log4.txt
write_on_log_txt log5.txt
write_on_log_txt log6.txt
write_on_log_txt log7.txt
write_on_log_txt log8.txt

cd ..

g++ process.cpp -o process

rm "$dir/results.ods"
./process "$dir/log.txt" soa.txt >> "$dir/results.ods"

