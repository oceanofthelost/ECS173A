#!/bin/bash

test()
{
    lambda="0.1 0.25 0.4 0.55 0.65 0.80 0.90"
    
    for i in $lambda
    do
        ./phase1 $i 1 $1 0
    done
}


buffersize="-1 1 20 50"

echo "lambda  Buffersize  Utilization  MeanBufferLength  DroppedPackets"

for i in $buffersize
do
    test $i
done
