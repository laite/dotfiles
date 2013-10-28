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
# git clone https://github.com/Lokaltog/vim-easymotion.git ~/.vim/bundle/vim-easymotion

# SuperTab
git clone https://github.com/ervandew/supertab.git ~/.vim/bundle/supertab

# SnipMate
# SnipMate depends on vim-addon-mw-utils and tlib
git clone https://github.com/tomtom/tlib_vim.git ~/.vim/bundle/tlib_vim
git clone https://github.com/MarcWeber/vim-addon-mw-utils.git ~/.vim/bundle/vim-addon-mw-utils
git clone https://github.com/garbas/vim-snipmate.git ~/.vim/bundle/vim-snipmate

# delimitMate
git clone https://github.com/Raimondi/delimitMate.git ~/.vim/bundle/delimitMate

# Vimple (needed by buffalo)
# git clone https://github.com/dahu/vimple.git ~/.vim/bundle/vimple

# Buffalo
# git clone https://github.com/Raimondi/vim-buffalo.git ~/.vim/bundle/vim-buffalo

# a.vim
git clone https://github.com/vim-scripts/a.vim.git ~/.vim/bundle/a.vim

# Surround
git clone https://github.com/tpope/vim-surround.git ~/.vim/bundle/vim-surround

# Ctrlp
git clone https://github.com/kien/ctrlp.vim.git ~/.vim/bundle/ctrlp.vim

# Syntastic
git clone https://github.com/scrooloose/syntastic.git ~/.vim/bundle/syntastic

# airline
git clone https://github.com/bling/vim-airline ~/.vim/bundle/vim-airline

#snippets for SnipMate come from different repository
git clone https://github.com/honza/vim-snippets.git ./vim-snippets
cp -rt ~/.vim vim-snippets/autoload vim-snippets/snippets

# Also install all the pretty colors
unzip vimColorSamplePack.zip -d ~/.vim
