#!/bin/bash

ROOTDIR=$1

cd $ROOTDIR

for ex in ./examples/*
do
    cd $ex
    echo Go to directory $ex
    make BINNAME=$(basename $ex) iar
    rm -rf build/
    cd ../..
done

