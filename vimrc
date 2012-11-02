" Use Vim settings, rather than Vi settings (much better!).
" This must be first, because it changes other options as a side effect.
set nocompatible

" one plugin to handle 'em all
call pathogen#infect()

" allow backspacing over everything in insert mode
set backspace=indent,eol,start
set t_Co=256
set backup		" keep a backup file
set history=50		" keep 50 lines of command line history
set ruler		" show the cursor position all the time
set showcmd		" display incomplete commands
set incsearch		" do incremental searching

" Don't use Ex mode, use Q for formatting
map Q gq

" CTRL-U in insert mode deletes a lot.  Use CTRL-G u to first break undo,
" so that you can undo CTRL-U after inserting a line break.
inoremap <C-U> <C-G>u<C-U>

set mouse=a

syntax on
set hlsearch
color tolerable

" laite - adds
set tabstop=4
set shiftwidth=4
set smartindent

" Automatic closing of ([{
inoremap {<CR> {<CR>}<Esc>ko
" inoremap ( ()<Esc>:let leavechar=")"<CR>i
" inoremap [ []<Esc>:let leavechar="]"<CR>i
" inoremap { {}<Esc>:let leavechar="}"<CR>i
" imap <C-j> <Esc>:exec "normal f" . leavechar<CR>a


map! <S-Insert> <MiddleMouse>
map <F2> <C-]> 

set nowrap
set ignorecase smartcase " ignore case on lowcase-searches
set number " row numbers
set scrolloff=10 " always +- 10 rows in sight
set sidescrolloff=5
set listchars=extends:>,precedes:<

" some key bindings
nnoremap <silent> ö :TagbarToggle<CR>
nnoremap ä :nohl<CR>



" Yankring
let g:yankring_history_dir = '/home/laite/.vim/'
nnoremap <silent> <F11> :YRShow<CR>

" EasyMotion
let g:EasyMotion_leader_key = '<Leader>'

" Tagbar
let g:tagbar_left = 1
let g:tagbar_compact = 1
let g:tagbar_autoclose = 1


" Only do this part when compiled with support for autocommands.
if has("autocmd")

  " Enable file type detection.
  " Use the default filetype settings, so that mail gets 'tw' set to 72,
  " 'cindent' is on in C files, etc.
  " Also load indent files, to automatically do language-dependent indenting.
  filetype plugin indent on

  " Put these in an autocmd group, so that we can delete them easily.
  augroup vimrcEx
  au!

  " For all text files set 'textwidth' to 78 characters.
  autocmd FileType text setlocal textwidth=78

  " When editing a file, always jump to the last known cursor position.
  " Don't do it when the position is invalid or when inside an event handler
  " (happens when dropping a file on gvim).
  " Also don't do it when the mark is in the first line, that is the default
  " position when opening a file.
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

