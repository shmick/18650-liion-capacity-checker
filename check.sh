#!/bin/bash

COMPLETE=$HOME/complete.txt

logcheck() {
done=$(tail -120 $HOME/serial.log | grep -v ^$ | /bin/grep -A4 "All batteries are discharged" | head -5 | tr "\t" " ")
}

logcheck

if [ -n "$done" ] && [ ! -f "$COMPLETE" ]
then
echo "$done" > $COMPLETE
$HOME/scripts/tweet.py "$(cat $HOME/complete.txt) @shmick"
elif [ -n "$done" ] && [ -f "$COMPLETE" ]
then
exit
elif [ -z "$done" ] && [ -f "$COMPLETE" ]
then
NOW=$(date +%Y-%m-%d-%H:%M)
mv $COMPLETE $COMPLETE.$NOW
elif [ -z "$done" ] && [ ! -f "$COMPLETE" ]
then
exit
fi
