#!/bin/bash

../bin/rshell << 'EOF'
echo #a
echo #"abcd"
ls #-a
ls #-l
#mkdir test
echo ab#cdefg
echo a #bcdefg
echo hello #world!
exit
EOF

