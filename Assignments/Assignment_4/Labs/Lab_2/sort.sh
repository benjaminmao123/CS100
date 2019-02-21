#!/bin/sh

array=(7 4 5 8 1)

size=${#array[@]}

for ((i=0; i < size; ++i))
do
    minVal=$i

    for ((j=$((i+1)); j < size; j++))
    do
	if (( array[j] < array[minVal] ))
	then
	    minVal=$j
	fi
    done
    
    temp=${array[i]}
    array[i]=${array[minVal]}
    array[minVal]=$temp
done

echo "${array[@]}"
    


