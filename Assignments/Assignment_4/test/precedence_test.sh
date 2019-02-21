#!/bin/sh

../bin/rshell << 'EOF'
(echo a && echo b) || (echo c && echo d)
(echo a)
(test -e src; echo b) && (test -f src/CommandReceiver.cpp; (echo d || echo e; (echo f && echo g))) && echo h
echo a; (test -d test; (echo c; echo d)) && (echo e && echo f)
echo a; (echo b; (echo c; echo d); echo e)
(echo a; echo b) || (echo c; echo d)
(echo a; (echo b && (echo c || (echo d; echo e))))
echo a && ((echo b || echo c) && echo d) && (test -e src/Main.cpp && echo e)
exit
EOF