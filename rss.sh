#!/bin/bash

CHANNEL="" # irc.server.#channel
TOKEN="" # fill in your token

while [ true ] ;
do
	info=()
	i=0
	rsstail -i 15 -l -u http://95.85.23.194/w/tiki-wiki_rss.php?TOKEN=$TOKEN -n 0 -a | while read x ;
	do
		#Set the field separator to new line
		IFS=$'\n'
		if [ -z "$x" ] ; then continue ; fi
		info[$i]=$x
		((i++))

		if [ $i -eq 3 ] ; 
		then
			i=0;
			info[0]=${info[0]/Title: /}
			info[1]=${info[1]/Link: /}
			#info[2]=${info[2]/Author: /}
			info[2]="Someone"
			echo "$CHANNEL *:: LobsterWiki :: ${info[2]} changed page \"${info[0]}\" - ${info[1]}" > /home/laite/.weechat/weechat_fifo_3061 ;
		fi
	done
done 
