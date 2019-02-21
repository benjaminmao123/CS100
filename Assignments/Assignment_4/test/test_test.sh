#!/bin/bash

../bin/rshell << 'EOF'
test -e header/CommandBase.h && echo CommandBase.h exists
[ -e CommandBase.h ] && echo CommandBase.h exists
test -d CommandBase.h || echo directory CommandBase.h does not exist
[ -f header/CommandBase.h ] && echo file Base.h exists
mkdir testpath
touch testfile.cpp
test -d testpath && echo directory testpath exists
test -f testfile.cpp && echo file testfile.cpp exists
rm -f testfile.cpp
rm -d testpath
[ -d testpath ] || echo directory testpath does not exist
test -f testfile.cpp || echo file testfile.cpp does not exist
exit
EOF