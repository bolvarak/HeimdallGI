#!/bin/bash

## Update
git pull;

## Generate make file
qmake;

## Compile
make && make clean;

## Remove the makefile
rm -fr Makefile;

## Execute the application
./Application.hgi

