#!/bin/bash

../bin/rshell << 'EOF'
echo a; echo b; echo c && ls && ls -a; b || echo d
<<<<<<< HEAD
ls -a; echo hello; mkdir testa
ls -a; echo hello && mkdir testb || echo world; git status
echo a && echo b; echo c || echo d && ls
echo "abcd"; echo df && ls -a
mkdir a; ls -l; ls -a || echo "done"
rm -d a
rm -d testa
rm -d testb
=======
ls -a; echo hello; mkdir test
ls -a; echo hello && mkdir test || echo world; git status
echo a && echo b; echo c || echo d && ls
echo "abcd"; echo df && ls -a
mkdir a; ls -l; ls -a || echo "done"
>>>>>>> 713b12410328b69a29f8799576778dea761526e9
exit
EOF