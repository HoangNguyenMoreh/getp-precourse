#!/bin/bash

output=$(python main.py)

if [ "$output" -ne "Success!!" ]; then
    exit 1
fi
