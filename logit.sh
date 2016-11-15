#!/bin/bash
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/local/games:/usr/games
nohup ttylog -f -b 115200 -d /dev/ttyAMA0 >> $HOME/serial.log & 
