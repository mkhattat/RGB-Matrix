#!/bin/sh

# cd ~/RGB-Matrix
stty -F /dev/ttyACM0 1200
bossac --port ttyACM0 -U false -e -w  -b main.bin -R
