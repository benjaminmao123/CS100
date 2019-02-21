#!/bin/bash

../bin/rshell << 'EOF'
cat < ../src/Main.cpp
touch test.txt
touch test1.txt
wc -l < test.txt
echo hello > test.txt
echo BJSHELL > test1.txt
ps -l > test.txt
ls -l > test1.txt
wc -l > test1.txt
cat < test.txt
cat < test.txt > test1.txt
grep PID < test1.txt
rm -f test.txt
rm -f test1.txt
exit
EOF