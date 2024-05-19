#!/bin/bash

text="\n\n\n\nLab Assignment for OS\n\n\n\nBy Niranjan Gopal\n\n\n\n"
formatted_text=$(echo -e "$text")
clear

for ((i=0; i<${#formatted_text}; i++)); do
    echo -n "${formatted_text:$i:1}"
    sleep 0.1
done

echo
