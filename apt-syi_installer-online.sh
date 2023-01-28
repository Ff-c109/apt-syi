#!/bin/bash
mkdir /opt/apt-syi || ((rm -r /opt/apt-syi && mkdir /opt/apt-syi) || exit 1)
curl -s https://raw.githubusercontent.com/Ff-c109/apt-syi/main/apt-syi.cpp > /opt/apt-syi/apt-syi.cpp &&\
curl -s https://raw.githubusercontent.com/Ff-c109/apt-syi/main/apt-syi.sh > /bin/apt-syi &&\
g++ /opt/apt-syi/apt-syi.cpp -o /opt/apt-syi/apt-syi &&\
echo "bash <(curl -s https://raw.githubusercontent.com/Ff-c109/apt-syi/main/apt-syi_OTA.sh)" > /opt/apt-syi/ota.sh &&\
echo "done." &&\
exit 0;

echo "error!" &&\
exit 1;
