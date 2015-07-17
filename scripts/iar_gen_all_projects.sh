#!/bin/bash

ROOTDIR=$1

cd $ROOTDIR

for ex in ./examples/*
do
    cd $ex
    echo Go to directory $ex
    make BINNAME=$(basename $ex) iar
    make BINNAME=$(basename $ex)_ddram VARIANT=ddram iar
    rm -rf build/
    cd ../..
done

