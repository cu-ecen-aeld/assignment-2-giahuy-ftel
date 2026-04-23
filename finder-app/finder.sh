#!/bin/sh

set -e
set -u

if [ "$#" -ne 2 ]; then 
    echo "Args must be 2"
    exit 1
fi

if [ ! -d "$1" ]; then
    echo "Arg 1 must be dir"
    exit 1
fi

echo "The number of files are $(find "$1" -type f | wc -l) and the number of matching lines are $(grep -r -c "$2" "$1" | wc -l)"
