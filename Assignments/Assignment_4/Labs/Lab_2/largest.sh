#!/bin/sh 

if [ $# != 3 ]
then
    echo "Incorrect number of parameters. Input exactly 3 parameters"
else
    result=$1

    if [ $2 -gt $result ]
    then
	result=$2
    fi
    if [ $3 -gt $result ]
    then    
	result=$3
    fi
    
    echo "$result"
fi
