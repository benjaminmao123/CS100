#!/bin/bash

../bin/rshell << 'EOF'
cat < ../src/Main.cpp
touch test.txt
wc -l < test.txt
echo hello JQ > test.txt
wc -l < test.txt
tr A-Z a-z < test.txt
echo it > test.txt
grep it < test.txt
cat < test.txt | tr A-Z a-z
echo 1 > test.txt
grep 1 < test.txt
rm -f test.txt
exit
EOF