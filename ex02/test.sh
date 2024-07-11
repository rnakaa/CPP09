#!/bin/bash

# Set the number of iterations
iterations=10

for ((i = 1; i <= iterations; i++)); do
    # Generate random numbers
    random_numbers=$(for j in {1..1000}; do printf "%d " "$((RANDOM % 99999 + 1))"; done)

    # Run the RPN command and capture the output
    output=$(./PmergeMe $random_numbers | tr '\n' '\n\n')

    # Split the output into two lines
    line1=$(echo "$output" | sed -n '1p' | sed 's/^ *//; s/ *$//')
    line2=$(echo "$output" | sed -n '2p' | sed 's/^ *//; s/ *$//')

    # Sort the original input numbers for comparison
    sorted_input=$(echo "$random_numbers" | tr ' ' '\n' | sort -n | tr '\n' ' ' | sed 's/^ *//; s/ *$//')

    # Compare the sorted lines with the sorted input
    if [ "$line1" != "$sorted_input" ] || [ "$line2" != "$sorted_input" ]; then
        echo "Test case $i:"
        echo "Input Numbers: $random_numbers"
        echo "Original Line 1: $line1"
        echo "Original Line 2: $line2"
        echo "Sorted Input:    $sorted_input"

        if [ "$line1" != "$sorted_input" ]; then
            echo "Line 1 is not correctly sorted."
        else
            echo "Line 1 is correctly sorted."
        fi

        if [ "$line2" != "$sorted_input" ]; then
            echo "Line 2 is not correctly sorted."
        else
            echo "Line 2 is correctly sorted."
        fi

        echo ""
    fi
done

