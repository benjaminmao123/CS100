#!/bin/sh

cat _.txt > $1.cc

echo >> $1.cc
echo "int main(int argc, const char** argv)" >> $1.cc
echo "{" >> $1.cc
echo "}" >> $1.cc




