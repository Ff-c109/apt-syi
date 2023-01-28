#!/bin/bash

if [[ $1 == "self" ]]
then
	mkdir /opt/apt-syi || ((rm -r /opt/apt-syi && mkdir /opt/apt-syi) || exit 1)
	cp ./apt-syi.cpp /opt/apt-syi &&\
	cp ./apt-syi.sh /bin/apt-syi &&\
	g++ -S /opt/apt-syi/apt-syi.cpp -o /opt/apt-syi/apt-syi.s &&\
	g++ /opt/apt-syi/apt-syi.s -o /opt/apt-syi/apt-syi &&\
	echo "done." &&\
	exit 0;

	echo "error!" &&\
	exit 1;
else
	sudo $0 self
fi
