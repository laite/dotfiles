" Use Vim settings, rather than Vi settings (much better!).
" This must be first, because it changes other options as a side effect.
set nocompatible

" one plugin to handle 'em all
call pathogen#infect()


set backspace=indent,eol,start " allow backspacing over everything in insert mode
set t_Co=256		" use 256 colors
set backup			" keep a backup file
set history=100		" keep 50 lines of command line history
set ruler			" show the cursor position all the time
set showcmd			" display incomplete commands
set incsearch		" do incremental searching
set mouse=a
syntax on
set hlsearch
set tabstop=4
set shiftwidth=4
set smartindent
set nowrap
set ignorecase smartcase " ignore case on lowcase-searches
set number " row numbers
set scrolloff=10 " always +- 10 rows in sight
set sidescrolloff=5
set listchars=extends:>,precedes:<

set foldcolumn=2
set foldmethod=manual
set foldnestmax=2
set foldminlines=1
set splitright

let mapleader = "ö"
inoremap <C-U> <C-G>u<C-U>
map <S-Insert> <MiddleMouse>
map! <S-Insert> <MiddleMouse>
map <F2> <C-]>

nnoremap <silent> <F3> :TagbarToggle<CR>
nnoremap ä :nohl<CR>
inoremap {<CR> {<CR>}<Esc>ko


" delete into abyss with R<motion>
nnoremap R "_d
" Use Q to start quick recording
nnoremap Q qq 

" some key bindings
"This allows for change paste motion cp{motion}
nmap <silent> cp :set opfunc=ChangePaste<CR>g@
function! ChangePaste(type, ...)
    silent exe "normal! `[v`]\"_c"
    silent exe "normal! p"
endfunction


""" Plugins """

" Yankring
let g:yankring_history_dir = '/home/laite/.vim/'
nnoremap <silent> <F11> :YRShow<CR>

" EasyMotion
let g:EasyMotion_leader_key = '<Leader>'

" Tagbar
let g:tagbar_left = 1
let g:tagbar_compact = 1
let g:tagbar_autoclose = 1


set directory=~/.vim/tmp/
set backupdir=~/.vim/tmp/

" Only do this part when compiled with support for autocommands.
if has("autocmd")

  " Enable file type detection.
  filetype plugin indent on

  " remember folding
  au BufWinLeave * silent! mkview
  au BufWinEnter * silent! loadview

  " Put these in an autocmd group, so that we can delete them easily.
  augroup vimrcEx
  au!

  " For all text files set 'textwidth' to 78 characters.
  autocmd FileType text setlocal textwidth=78

  " When editing a file, always jump to the last known cursor position.
  autocmd BufReadPost *
    \ if line("'\"") > 1 && line("'\"") <= line("$") |
    \   exe "normal! g`\"" |
    \ endif

  augroup END

else
  set autoindent		" always set autoindenting on
endif " has("autocmd")

if !exists(":DiffOrig")
  command DiffOrig vert new | set bt=nofile | r ++edit # | 0d_ | diffthis
		  \ | wincmd p | diffthis
endif

" set pretty colors
color jellybeans
