#!/bin/sh
backupped="Made backups for the following file(s): "

if [ -f ~/.vimrc ]; then
	mv ~/.vimrc ~/.vimrc_backup
	backupped="$backupped .vimrc"
fi

if [ -f ~/.gvimrc ]; then
	mv ~/.gvimrc ~/.gvimrc_backup
	backupped="$backupped .gvimrc"
fi

if [ -f ~/.numbermaps.vim ]; then
	mv ~/.numbermaps.vim ~/.numbermaps.vim_backup
	backupped="$backupped .numbermaps.vim"
fi

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

ln -s /home/machina/workspace/dotfiles/vimrc ~/.vimrc
ln -s /home/machina/workspace/dotfiles/gvimrc ~/.gvimrc
ln -s /home/machina/workspace/dotfiles/numbermaps.vim ~/.numbermaps.vim
ln -s /home/machina/workspace/dotfiles/bashrc ~/.bashrc
ln -s /home/machina/workspace/dotfiles/bash_aliases ~/.bash_aliases
ln -s /home/machina/workspace/dotfiles/bash_functions ~/.bash_functions
ln -s /home/machina/workspace/dotfiles/Xresources ~/.Xresources

echo "All is well"
echo $backupped
