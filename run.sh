#!/bin/bash

## Clear Screen
clear;

## Update
git pull;

## Generate make file
cmake .;

## Compile
make && make clean;

## Remove the makefile
rm -fr Makefile;

## Execute the application
./app.hgi

