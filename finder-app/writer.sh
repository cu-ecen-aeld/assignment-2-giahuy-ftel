#!/bin/bash

set -eu

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <writefile> <writestr>"
    exit 1
fi

writefile="$1"
writestr="$2"


if [ -z "$writestr" ]; then
    echo "Sencond arg must not be empty"
    exit 1
fi

if ! mkdir -p $(dirname "$writefile"); then
    echo "Could not create $(dirname "$writefile")"
    exit 1
fi

if ! echo "$writestr" > "$writefile"; then
    echo "Could not echo to $(dirname "$writefile")"
    exit 1
fi
