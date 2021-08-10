#!/bin/bash

dir=$1
pfx_log=$2

echo -n "" > "$pfx_log-log1".txt
echo -n "" > "$pfx_log-log2".txt
echo -n "" > "$pfx_log-log3".txt
echo -n "" > "$pfx_log-log4".txt
echo -n "" > "$pfx_log-log5".txt
echo -n "" > "$pfx_log-log6".txt
echo -n "" > "$pfx_log-log7".txt
echo -n "" > "$pfx_log-log8".txt

sh experiment.sh 4 "$pfx_log-log1".txt $dir &
#sh experiment.sh 4 "$pfx_log-log2".txt $dir &
#sh experiment.sh 4 "$pfx_log-log3".txt $dir &
#sh experiment.sh 4 "$pfx_log-log4".txt $dir &
#sh experiment.sh 4 "$pfx_log-log5".txt $dir &
#sh experiment.sh 4 "$pfx_log-log6".txt $dir &
#sh experiment.sh 4 "$pfx_log-log7".txt $dir &
#sh experiment.sh 4 "$pfx_log-log8".txt $dir &
