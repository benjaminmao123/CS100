#!/bin/bash

../bin/rshell << 'EOF'
echo "a"
echo "b"
echo "c"
ls
ls -a
ls -l
echo "a""""abbcd"
mkdir a
git status
hostname
echo a b c d e f g
rm -d a
exit
EOF