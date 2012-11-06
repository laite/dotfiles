#!/bin/bash

#create status-string with 'start'-bar
st=""

# check for completed torrents
if [ $(ls -1A /home/laite/Downloads/Download\ Complete/ | wc -l) -ne 0 ]; then
	    st="$st<span color=\"#198A9C\"> torrent  </span>" 
fi

# echo out only if there's something worth noting
if [ "$st" != "" ]
then
	echo "$st"
fi

