#!/bin/bash

if ! [[ -f `which nmap` ]]; then
    echo "nmap not found, installing"
    sudo apt-get -y install nmap
fi

if ! [[ -f `which arp` ]]; then
    echo "arp not found, installing"
    sudo apt-get -y install net-tools
fi

echo "scanning net"
nmap -sP 192.168.1.1-254 >> /dev/null
arp -a | grep $1 > finded.conf   # $1 - searching mac
