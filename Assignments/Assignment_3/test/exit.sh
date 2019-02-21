#!/bin/sh

../bin/rshell << 'EOF'
exit
echo a && exit
echo a && echo b; echo c; ls && exit
echo ab; a || echo b && exit
ls -a; ls -l; mkdir c && exit
exit && echo a
echo exit
exit
EOF

