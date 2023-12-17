output=$(python main.py)  # Replace 'python' with 'python3' if using Python 3

if [ "$output" -ne "Success!!" ]; then
    exit 1
fi
