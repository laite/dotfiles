#!/bin/bash
# this script installs my favourite vim scripts from github

mkdir -p ~/.vim/tmp
mkdir -p ~/.vim/autoload
mkdir -p ~/.vim/bundle

# Pathogen
git clone https://github.com/tpope/vim-pathogen.git
cp ./vim-pathogen/autoload/pathogen.vim ~/.vim/autoload
rm -rf vim-pathogen

# Tagbar
git clone git://github.com/majutsushi/tagbar ~/.vim/bundle/tagbar 

# EasyMotion
git clone https://github.com/Lokaltog/vim-easymotion.git ~/.vim/bundle/vim-easymotion

# SuperTab
git clone https://github.com/ervandew/supertab.git ~/.vim/bundle/supertab

# SnipMate
git clone https://github.com/msanders/snipmate.vim.git ~/.vim/bundle/snipmate.vim

# Also install all the pretty colors
unzip vimColorSamplePack.zip -d ~/.vim
