#!/bin/sh
backupped="Made backups for the following file(s): "

if [ -f ~/.bashrc ]; then
	mv ~/.bashrc ~/.bashrc_backup
	backupped="$backupped .bashrc"
fi

if [ -f ~/.bash_aliases ]; then
	mv ~/.bash_aliases ~/.bash_aliases_backup
	backupped="$backupped .bash_aliases"
fi

if [ -f ~/.bash_functions ]; then
	mv ~/.bash_functions ~/.bash_functions_backup
	backupped="$backupped .bash_functions"
fi

if [ -f ~/.Xresources ]; then
	mv ~/.Xresources ~/.Xresources_backup
	backupped="$backupped .Xresources"
fi

ln -s /home/laite/.files/bashrc ~/.bashrc
ln -s /home/laite/.files/bash_aliases ~/.bash_aliases
ln -s /home/laite/.files/bash_functions ~/.bash_functions
ln -s /home/laite/.files/Xresources ~/.Xresources

echo "All is well"
echo $backupped
