#!/bin/bash

../bin/rshell << 'EOF'
test -e header/CommandBase.h && echo CommandBase.h exists
[ -e CommandBase.h ] && echo CommandBase.h exists
test -d CommandBase.h || echo directory CommandBase.h does not exist
[ -f header/CommandBase.h ] && echo Base.h exists
mkdir path
touch file.cpp
test -d path && echo path exists
test -f file.cpp && echo file.cpp exists
rm file.cpp
rm -r path
[ -d path ] || echo directory path does not exist
test -f file.cpp || echo file.cpp does not exist
exit
EOF