#!/bin/sh
if [ $# = 1 ]
then
	gcc "$1" -o prog
	exit_code=$?
	if [ $exit_code != 0 ]
	then
		vi $1
	fi
else
	echo "num_params ==0 or >1"
fi
