#!/bin/bash

../bin/rshell << 'EOF'
cat < ../src/Main.cpp
touch test.txt
touch test1.txt
echo this is the 2nd test >> test1.txt
echo JQ ILY >> test.txt
ls >> test.txt
ps >> test.txt
wc >> test.txt
ls >> test1.txt
ps >> test1.txt
wc >> test1.txt
ls -l >> test.txt
ls -l >> test1.txt
rm -f test.txt
rm -f test1.txt
exit
EOF