#!/bin/bash

../bin/rshell << 'EOF'
echo a; echo b; echo c && ls && ls -a; b || echo d
ls -a; echo hello; mkdir test
ls -a; echo hello && mkdir test || echo world; git status
echo a && echo b; echo c || echo d && ls
echo "abcd"; echo df && ls -a
mkdir a; ls -l; ls -a || echo "done"
exit
EOF