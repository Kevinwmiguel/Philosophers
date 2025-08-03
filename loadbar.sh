#!/bin/bash

bar="##################################################"
bar_length=${#bar}

echo -ne "\033[0;32m[                                                  ]\033[0m"

for i in $(seq 1 $bar_length); do
    sleep 0.02
    echo -ne "\r\033[0;32m[${bar:0:$i}\033[0;37m${bar:$i}]\033[0m"
done

echo -e "\n Build completa!"
