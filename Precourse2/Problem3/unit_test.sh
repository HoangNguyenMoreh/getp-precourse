#!/bin/bash

output=$(python main.py)

if [ "$output" != "Success!!" ]; then
    exit 1
fi
