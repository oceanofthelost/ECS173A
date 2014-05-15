#!/bin/bash

test()
{
    #Lambda for infinite buffer size
    lambda="0.1 0.25 0.4 0.55 0.65 0.80 0.90"
    #Lambda for finite buffer size
    lambda2="0.2 0.4 0.6 0.8 0.9"
    
    if (($1 == -1)); then
        for i in $lambda
        do
            #./phase1 lambda mu buffer-size [Exponential,Pareto] File
            ./phase1 $i 1 $1 $2 File
        done
    else
        for i in $lambda2
        do
            #./phase1 lambda mu buffer-size [Exponential,Pareto] File
            ./phase1 $i 1 $1 $2 File
        done
    fi
}


buffersize="-1 1 20 50"

echo "Lambda,Buffersize,Utilization,MeanBufferLength,DroppedPackets"

#for i in $buffersize
#do
#    test $i "Exponential"
#done

for i in $buffersize
do
    test $i "Pareto"
done