#!/usr/bin/env bash

set -e

CWD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

IFS=$'\n'

FLAGS=("-O3 -fPIC -march=native -DNDEBUG")

mkn clean build -tSa "${FLAGS[@]}" -l -pthread -d + 

for F in $(grep -lR "int main(" | grep -v "mkn.sh"); do
	F=$(basename $F)
	echo $F
	mkn clean build -tSa "${FLAGS[@]}" -l -pthread run -M $F  
done
