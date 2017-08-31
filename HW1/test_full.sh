#!/bin/bash

FILE="warmup_small"
gcc "$FILE.c" -o "$FILE.exe"

for i in `seq 1 $1` 
do
	echo "Running test $i"
	./"$FILE.exe" < "tests/test$i.in" > "tests/test$i.res" && diff "tests/test$i.out" "tests/test$i.res"
	rm tests/test$i.res
done

rm "$FILE.exe"
