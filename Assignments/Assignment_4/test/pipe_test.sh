#!/bin/sh

../bin/rshell << 'EOF'
ls -l | wc -l
echo a | echo b | echo c
touch test.txt
echo a > test.txt
cat < test.txt | wc -l
cat < test.txt | tr A-Z a-z | tee test2.txt | tr a-z A-Z > test3.txt
echo a && echo b | tr A-Z a-z > test.txt && cat < test.txt | tr a-z A-Z > test2.txt
echo c || echo d | tr A-Z a-z >> test.txt && cat < test.txt | tr a-z A-Z >> test2.txt
rm -f test.txt
rm -f test2.txt
rm -f test3.txt
exit
EOF