#!/bin/sh
if [ $# = 1 ]
then
	echo "param = $1"
elif [ $# > 1 ]
then
	echo "params:"
	for i in $@
	do
		echo "$i "
	done	
else
	echo "no param"
fi
