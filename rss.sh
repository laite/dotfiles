#!/bin/bash

WEECHAT_FOLDER="" # /path/to/.weechat
CHANNEL="" # irc.server.#channel
TOKEN="" # fill in your token
TIMEOUT=600 # seconds to wait before announcing same page

while [ true ] ;
do
	info=()
	i=0
	lasttime=$(date +%s --date "$timeout seconds ago")
	lastpage=""

	rsstail -i 15 -l -u http://95.85.23.194/w/tiki-wiki_rss.php?TOKEN=$TOKEN -n 0 -a | while read x ;
	do
		#Set the field separator to new line
		IFS=$'\n'

		if [ -z "$x" ] ; then continue ; fi

		info[$i]=$x
		((i++))
		now=$(date +%s)
		elapsed=$((now-lasttime))

		if [ $i -eq 3 ] ; 
		then
			if [ $elapsed -ge $TIMEOUT ] || [ "$lastpage" != "$info[0]" ] ;
			then
				i=0;
				lasttime=$(date +%s)
				lastpage=$info[0]
				info[0]=${info[0]/Title: /}
				info[1]=${info[1]/Link: /}
				#info[2]=${info[2]/Author: /}
				info[2]="Someone"
				echo "$CHANNEL *:: LobsterWiki :: ${info[2]} changed page \"${info[0]}\" - ${info[1]}" > $WEECHAT_FOLDER/weechat_fifo_* ;
			fi
		fi
	done
done 
