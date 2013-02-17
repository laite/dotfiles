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
set history=100					" keep 50 lines of command line history
set ruler						" show the cursor position all the time
set showcmd						" display incomplete commands
set incsearch					" do incremental searching
set mouse=a						" enable mouse for all modes
set hlsearch					" highlight search results
set tabstop=4					" number of spaces a tab counts for
set shiftwidth=4				" number of spaces for (auto)indent
set smartindent					" start new lines indented
set nowrap						" don't wrap long lines
set ignorecase smartcase 		" ignore case on lowcase-searches
set number 						" row numbers
set scrolloff=10 				" always +- 10 rows in sight
set sidescrolloff=5				" always +- 5 columns
set linebreak
set showbreak=\ ->\ 

set listchars=extends:>,precedes:<

" foldingmethods for gvim are specified in .gvimrc (they differ a bit)
set foldcolumn=2
set foldmethod=manual
set foldnestmax=2
set foldminlines=1

let mapleader = "ö"
map <S-Insert> <MiddleMouse>
map! <S-Insert> <MiddleMouse>
map <F4> :sp %:p:s,.h$,.X123X,:s,.cpp$,.h,:s,.X123X$,.cpp,<CR>

" commandline mappings
cnoreabbrev vhelp belowright vert help
" make ctrl-p and ctrl-n behave like Up/Down-keys on command line
cnoremap <C-p> <Up>
cnoremap <C-n> <Down>

" normal mode mappings
nnoremap <silent> <F3> :TagbarToggle<CR>
nnoremap <silent> <Leader>ä :nohl<CR>
" create empty lines and return to normal mode
nnoremap <Leader>o o<Esc>
nnoremap <Leader>O O<Esc>
" delete into abyss with öd<motion>
nnoremap <Leader>d "_d
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

" insert mode mappings
inoremap <C-U> <C-G>u<C-U>

" autocomplete { and newline, move cursor to middle
inoremap {<CR> {<CR>}<Esc>O

" complete brackets, make <c-l> exit latest, <leader><c-l> the one before that
let leavechar=""
inoremap ( ()<Esc>:let lastleavechar=leavechar<CR>:let leavechar=")"<CR>i
inoremap [ []<Esc>:let lastleavechar=leavechar<CR>:let leavechar="]"<CR>i
inoremap { {}<Esc>:let lastleavechar=leavechar<CR>:let leavechar="}"<CR>i
inoremap < <><Esc>:let lastleavechar=leavechar<CR>:let leavechar=">"<CR>i
inoremap " ""<Esc>:let lastleavechar=leavechar<CR>:let leavechar="\""<CR>i
inoremap ' ''<Esc>:let lastleavechar=leavechar<CR>:let leavechar="\'"<CR>i
imap <C-L> <Esc>:exec "normal f" . leavechar<CR>a
imap <Leader><C-L> <Esc>:exec "normal f" . lastleavechar<CR>a

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

""" Plugins """

" EasyMotion
let g:EasyMotion_leader_key = '<Leader>'

" Tagbar
let g:tagbar_left = 1
let g:tagbar_compact = 1
let g:tagbar_autoclose = 1

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

" buffalo
let buffalo_autoaccept = 1

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

  " remember folding
  au BufWinLeave * silent! mkview
  au BufWinEnter * silent! loadview

  " hide search highlighting when entering insert mode
  " new search through / or ? returns hls, as do letters n and N
  autocmd InsertEnter * :set nohlsearch

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

  " automatically reload vimrc when it's saved
  au BufWritePost .vimrc so ~/.vimrc

  autocmd Syntax cpp call EnhanceCppSyntax()
  " don't use cpp11 additions by default
  " au BufNewFile,BufRead *.cpp set syntax=cpp11

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
