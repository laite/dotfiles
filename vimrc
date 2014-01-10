" Use Vim settings, rather than Vi settings (much better!).
" This must be first, because it changes other options as a side effect.
set nocompatible

" one plugin to handle 'em all
call pathogen#infect()

syntax on						" make pretty colors
set shortmess+=I				" hide start screen
set backspace=indent,eol,start 	" allow backspacing over everything in insert mode
set t_Co=256					" use 256 colors
set backup						" keep a backup file
set history=200					" keep 200 lines of command line history
set ruler						" show the cursor position all the time
set showcmd						" display incomplete commands
set incsearch					" do incremental searching
set mouse=a						" enable mouse for all modes
set hlsearch					" highlight search results
set tabstop=4					" number of spaces a tab counts for
set noexpandtab					" don't handle tab as spaces
set shiftwidth=4				" number of spaces for (auto)indent
"set softtabstop=4				" number of spaces that a <tab> counts
set smartindent					" start new lines indented
set nowrap						" don't wrap long lines
set ignorecase smartcase 		" ignore case on lowcase-searches
set scrolloff=5 				" always +- 5 rows in sight
set sidescrolloff=5				" always +- 5 columns
set linebreak
set showbreak=\ -->\ 
set number
set relativenumber				" use relative numbers by default

set listchars=extends:>,precedes:<

" foldingmethods for gvim are specified in .gvimrc (they differ a bit)
set foldcolumn=2
set foldmethod=indent
set foldnestmax=2
set foldminlines=1

let javaScript_fold=1         " JavaScript
let perl_fold=1               " Perl
let php_folding=1             " PHP
let r_syntax_folding=1        " R
let ruby_fold=1               " Ruby
let sh_fold_enabled=1         " sh
let vimsyn_folding='af'       " Vim script
let xml_syntax_folding=1      " XML

let mapleader = "ö"
let g:is_bash=1
map <S-Insert> <MiddleMouse>
map! <S-Insert> <MiddleMouse>
map <Leader>h :A<CR>

" commandline mappings
cnoreabbrev vhelp belowright vert help
" make ctrl-p and ctrl-n behave like Up/Down-keys on command line
cnoremap <C-p> <Up>
cnoremap <C-n> <Down>
" add helpful path expander - command on active buffer
cnoremap <expr> %% getcmdtype() == ':' ? expand('%:h').'/' : '%%'

" normal mode mappings
nnoremap <silent> <Leader>ä :nohl<CR>
" create empty lines and return to normal mode
nnoremap <Leader>o o<Esc>
nnoremap <Leader>O O<Esc>
nnoremap <Leader><Leader>o o<ESC>kO<ESC>j

" delete row's contents with leader-d
nnoremap <Leader>d ^D
" treat c-h as real backspace also in normal mode
nnoremap <C-H> "_X
" make Y behave like C and D (yank to the end of line)
nnoremap Y y$
" easier jumping between windows and tabs
nnoremap <C-j> <C-w>w
nnoremap <C-k> <C-w>W
nnoremap <C-h> gT
nnoremap <C-l> gt
" entering insert mode hides hlsearch, but we want to get it back with n and N
nnoremap n :set hlsearch<CR>n
nnoremap N :set hlsearch<CR>N
" use <c-p> immediately on the command line
nnoremap <C-p> :<C-p>
" make some use for 'ä'
nnoremap ä `
nnoremap ää ``
nnoremap Ä %
vnoremap ä `
vnoremap ää ``
vnoremap Ä %

" use - as backwards search
nnoremap - ?
vnoremap - ?

" insert mode mappings
inoremap <C-U> <C-G>u<C-U>

" autocomplete { and newline, move cursor to middle
inoremap {<CR> {<CR>}<Esc>O

" complete brackets, make <c-l> exit latest, <leader><c-l> the one before that
let leavechar=""
" inoremap ( ()<Esc>:let lastleavechar=leavechar<CR>:let leavechar=")"<CR>i
" inoremap [ []<Esc>:let lastleavechar=leavechar<CR>:let leavechar="]"<CR>i
" inoremap { {}<Esc>:let lastleavechar=leavechar<CR>:let leavechar="}"<CR>i
" inoremap < <><Esc>:let lastleavechar=leavechar<CR>:let leavechar=">"<CR>i
" inoremap " ""<Esc>:let lastleavechar=leavechar<CR>:let leavechar="\""<CR>i
" inoremap ' ''<Esc>:let lastleavechar=leavechar<CR>:let leavechar="\'"<CR>i
" imap <C-L> <Esc>:exec "normal f" . leavechar<CR>a
" imap <Leader><C-L> <Esc>:exec "normal f" . lastleavechar<CR>a

" by default, brackets are autocompleted, we can skip this with leader-key
inoremap <Leader>[ [
inoremap <Leader>( (
inoremap <Leader>{ {
inoremap <Leader>< <
inoremap <Leader>" "
inoremap <Leader>' '

" also, we'll add << to an exception (useful in cpp)
inoremap << <<

" since we use ö also as a <leader>, we define 'öö' as a simple 'ö'
inoremap <Leader>ö ö
" make C-p into <esc> until I figure out something better
inoremap <C-p> <Esc>


" join with previous line and continue from middle
inoremap <C-K>k <Esc>kJi
" join with previous line and continue from the end
inoremap <C-K>a <Esc>kJA
" join with previous line and exit insert mode
inoremap <C-K>[ <Esc>kJ
" make <C-J> add ; and newline
inoremap <C-J> ;<CR>

" c-b is currently not used
" inoremap <C-B>


" other key bindings
"This allows for change paste motion cp{motion}
nmap <silent> cp :set opfunc=ChangePaste<CR>g@
function! ChangePaste(type, ...)
    silent exe "normal! `[v`]\"_c"
    silent exe "normal! p"
endfunction

" define motion 'numbers' in external file
source $HOME/.numbermaps.vim

" add quick way to toggle between normal and relative line numbers
function! NumberToggle()
	if(&relativenumber == 1)
		set norelativenumber
	else
		set relativenumber
	endif
endfunc

nnoremap <C-n> :call NumberToggle()<cr>


""" Plugins """


" EasyMotion
let g:EasyMotion_leader_key = '<Leader>'

" Tagbar
let g:tagbar_left = 1
let g:tagbar_compact = 1
let g:tagbar_autoclose = 1
nnoremap <Leader>t :TagbarToggle<CR>

" Set separate Supertab settings for terminal and gvim
if has('gui_running')
	let g:SuperTabMappingTabLiteral = '<C-Tab>'
	let g:SuperTabMappingForward = '<Tab>'
	let g:SuperTabMappingBackward = '<C-S-Tab>'
else
	let g:SuperTabMappingTabLiteral = '<tab>'
	" <C-@> in terminal equals control-space
	let g:SuperTabMappingForward = '<C-@>'
	let g:SuperTabMappingBackward = '<S-C-@>'
endif

" ctrlp
let g:ctrlp_follow_symlinks = 1
let g:ctrlp_map = '<Leader>f'
let g:ctrlp_max_height = 25
let g:ctrlp_working_path_mode = ''
let g:ctrlp_use_caching = 25
let g:ctrlp_switch_buffer = 't'
let g:ctrlp_open_multiple_files = '2vjr'

nnoremap <Leader>b :CtrlPBuffer<CR>
nnoremap <Leader>g :CtrlPBufTag<CR>
nnoremap <Leader>G :CtrlPBufTagAll<CR>
nnoremap <Leader>F :CtrlP %:h<CR>


" delimitMate
" use <C-l> in insert mode for escaping brackets
imap <C-l> <Plug>delimitMateS-Tab
imap <Leader><C-l> <Plug>delimitMateJumpMany

" Syntastic

" Airline
let g:airline#extensions#whitespace#enabled = 0
let g:airline_theme="jellybeans"

" tComment
nnoremap <Leader>C :TCommentBlock<CR>
vnoremap <Leader>C :TCommentBlock<CR>
nnoremap <Leader>c :TComment<CR>
vnoremap <Leader>c :TComment<CR>

" dbgPaVim

let g:dbgPavimPort = 9009
let g:dbgPavimBreakAtEntry = 0
nnoremap <Leader>p :Bp<CR>


""" Plugins End """


set directory=~/.vim/tmp/
set backupdir=~/.vim/tmp/

" don't save basic options or folds with the session
set ssop-=options
set ssop-=folds

" Add highlighting for function definition in C++
function! EnhanceCppSyntax()
  syn match cppFuncDef "::\~\?\zs\h\w*\ze([^)]*\()\s*\(const\)\?\)\?\(\:\)\?$"
  hi def link cppFuncDef Special
endfunction

" Only do this part when compiled with support for autocommands.
if has("autocmd")

  " Enable file type detection.
  filetype plugin indent on

  " set manual folding only for textfiles and files without syntax, and remember it
  au Syntax text setlocal foldmethod=manual
  au BufWinLeave ?* if &syntax == 'text' | mkview! | endif
  au BufWinEnter ?* if &syntax == 'text' | silent! loadview | endif

  au BufWinLeave ?* if &syntax == '' | mkview! | endif
  au BufWinEnter ?* if &syntax == '' | silent! loadview | endif

  " hide search highlighting when entering insert mode
  " new search through / or ? returns hls, as do letters n and N
  autocmd InsertEnter * :set nohlsearch

  " Put these in an autocmd group, so that we can delete them easily.
  augroup vimrcEx
  au!

  " When editing a file, always jump to the last known cursor position.
  autocmd BufReadPost *
    \ if line("'\"") > 1 && line("'\"") <= line("$") |
    \   exe "normal! g`\"" |
    \ endif

  " enhance highlighting some functions
  autocmd Syntax cpp call EnhanceCppSyntax()

  " don't automatically add commentmark when creating newline with o/O
  autocmd FileType cpp set fo-=o

  " don't use cpp11 additions by default
  " au BufNewFile,BufRead *.cpp set syntax=cpp11
  
  " use external browser through script with php files
  autocmd FileType php set keywordprg=~/.vim/php_doc

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
