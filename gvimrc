" .gvimrc, by Markus Klinga

set ch=1
set guioptions=agit
set guicursor+=a:blinkon0
set shortmess+=I
set mousehide		" Hide the mouse when typing text

set foldcolumn=3
set foldmethod=syntax
set foldnestmax=2
set foldminlines=1

" Make shift-insert work like in Xterm
map <S-Insert> <MiddleMouse>
map! <S-Insert> <MiddleMouse>
map <F2> <C-]>

" delete into abyss with R<motion>
nnoremap R "_d

"This allows for change paste motion cp{motion}
nmap <silent> cp :set opfunc=ChangePaste<CR>g@
function! ChangePaste(type, ...)
    silent exe "normal! `[v`]\"_c"
    silent exe "normal! p"
endfunction



" Only do this for Vim version 5.0 and later.
if version >= 500

  " I like highlighting strings inside C comments
  let c_comment_strings=0

  " Switch on syntax highlighting if it wasn't on yet.
  if !exists("syntax_on")
    syntax on
  endif

  " Switch on search pattern highlighting.
  set hlsearch
endif

color laite04
set spelllang=en_us



