" .gvimrc, by Markus Klinga
" most options are already set up in .vimrc!

set ch=1
set guioptions=agit
set guicursor+=a:blinkon0
set shortmess+=I
set mousehide		" Hide the mouse when typing text

" we presume that gvim is mostly for coding
" whereas vim is all-around editor
set foldcolumn=3
set foldmethod=syntax
set foldnestmax=2
set foldminlines=1

" Supertab
let g:SuperTabMappingTabLiteral = '<s-tab>'
let g:SuperTabMappingForward = '<tab>'
let g:SuperTabMappingBackward = '<s-c-space>'

color laite04
