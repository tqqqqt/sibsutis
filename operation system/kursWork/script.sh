#!/bin/bash
if [ -n "$1" ]
then
	if [ "$1" = "make" ]
	then
		cp kwread.service /etc/systemd/system/kwread.service
		cp bin/server /usr/sbin/kwreadelf
	elif [ "$1" = "clear" ]
	then
		rm /etc/systemd/system/kwread.service
		rm /usr/sbin/kwreadelf
	fi
else
	echo "No param."
fi
