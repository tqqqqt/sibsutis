#!bin/sh
if [ $# = 1 ] 
then
	pidin | grep $1
else
	echo " num_param > 1"
fi
