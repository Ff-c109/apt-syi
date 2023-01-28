#!/bin/bash

COUNTER=`curl -s https://raw.githubusercontent.com/Ff-c109/apt-syi/main/COUNTER`

counter=`cat /opt/apt-syi/COUNTER`

if [[ $counter == $COUNTER ]]
then
	echo "OTA: do nothing."
else
	bash <(curl -s https://raw.githubusercontent.com/Ff-c109/apt-syi/main/apt-syi_installer-online.sh)
	curl -s https://raw.githubusercontent.com/Ff-c109/apt-syi/main/COUNTER > /opt/apt-syi/COUNTER
	echo "OTA: Auto fetch"
fi

