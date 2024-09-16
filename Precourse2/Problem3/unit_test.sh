#!/bin/bash

output=$(python main.py)

if [ "$output" != "Su" ]; then
    exit 1
fi
