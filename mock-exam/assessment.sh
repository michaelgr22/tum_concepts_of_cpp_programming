#!/bin/bash
POINTS=0
BASE=`pwd`
rm -f summary.txt
while IFS= read -r line || [ -n "$line" ]; do
    cd $BASE
    if [[ "$line" == */eval.sh ]]; then
        DIR="$(dirname "${line}")"
        echo $DIR >> summary.txt
        cd $DIR
        timeout 2m bash eval.sh
        if [[ $? -eq 0 ]]; then
            POINTS=$((POINTS + 1))
        fi
    fi
done < .keep

echo
echo
cat summary.txt