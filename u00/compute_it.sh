#!/usr/bin/env bash
i=0
while [[ $i -lt 10 ]]
do 
    echo $((i ** $1))
    sleep 1
    ((i++))
done

