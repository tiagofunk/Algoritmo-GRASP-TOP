#!/bin/bash

export IRACE_HOME=/home/tiago/R/x86_64-pc-linux-gnu-library/3.4/irace
export PATH=${IRACE_HOME}/bin/:$PATH

cd ..
cd Project

make build

cd ..
cd irace

rm target-runner

cp "../Project/TOP_GRASP_TS_PR" "./target-runner"

irace --parallel 8 >> log_irace.txt

