" Vim color file
" Original Maintainer:  Lars H. Nielsen (dengmao@gmail.com)
" Last Change:  2010-07-23
"
" Laite06, 'goes dark'
" inspired by wombat, that was inspired by David Liang's version (bmdavll@gmail.com)

set background=dark

hi clear

if exists("syntax_on")
	syntax reset
endif

let colors_name = "laite07"

" basic view formatting
hi Normal		guifg=#657c80	guibg=#002029	gui=none
hi NonText		guifg=#657c80	guibg=#033342	gui=none
hi TabLine    	gui=none guifg=#657c80 guibg=#033342
hi TabLineSel   gui=bold guifg=#f6f3e8   guibg=#033342
hi TabLineFill	gui=none guifg=#666666   guibg=#033342

hi FoldColumn	gui=none guifg=#999999 guibg=#002b36
hi SignColumn	gui=none guifg=#999999 guibg=#f0f0f0
hi SignColumn	guifg=#a0a8b0	guibg=#384048	gui=none

hi StatusLine   gui=none guibg=#9899ea guifg=#333333
hi StatusLineNC gui=none guibg=#bbbbbb guifg=white
hi VertSplit    gui=none guibg=#333333 guifg=#999999

" General colors
hi Cursor		guifg=NONE		guibg=#657c80	gui=none
hi Visual		guifg=#657c80	guibg=#cfddbc	gui=none
" hi VisualNOS
" hi Search
hi Folded		ctermfg=103		ctermbg=238		cterm=none		guifg=#a0a8b0	guibg=#002029	gui=none
hi Title		ctermfg=7		ctermbg=none	cterm=bold		guifg=#f6f3e8	guibg=NONE		gui=bold
hi StatusLine	ctermfg=7		ctermbg=238		cterm=none		guifg=#f6f3e8	guibg=#444444	gui=none
hi VertSplit	ctermfg=238		ctermbg=238		cterm=none		guifg=#444444	guibg=#444444	gui=none
hi StatusLineNC	ctermfg=243		ctermbg=238		cterm=none		guifg=#857b6f	guibg=#444444	gui=none
hi LineNr		ctermfg=243		ctermbg=0		cterm=none		guifg=#857b6f	guibg=#002b36	gui=none
hi SpecialKey	ctermfg=244		ctermbg=236		cterm=none		guifg=#808080	guibg=#343434	gui=none

" Vim >= 7.0 specific colors
if version >= 700
hi CursorLine					ctermbg=236		cterm=none						guibg=#2d2d2d
hi MatchParen	ctermfg=7		ctermbg=243		cterm=bold		guifg=#f6f3e8	guibg=#857b6f	gui=bold
hi Pmenu		ctermfg=7		ctermbg=238						guifg=#f6f3e8	guibg=#444444
hi PmenuSel		ctermfg=0		ctermbg=192						guifg=#000000	guibg=#cae682
endif


" Syntax highlighting
hi Keyword		ctermfg=111		cterm=none		guifg=#cfddbc	gui=none
hi Statement	ctermfg=111		cterm=none		guifg=#f58900	gui=none
hi Constant		ctermfg=173		cterm=none		guifg=#f58900	gui=none
hi Number		ctermfg=173		cterm=none		guifg=#f58900	gui=none
hi PreProc		ctermfg=173		cterm=none		guifg=#f58900	gui=none
hi Function		ctermfg=192		cterm=none		guifg=#10858b	gui=none
hi Identifier	ctermfg=192		cterm=none		guifg=#21a198	gui=none
hi Type			ctermfg=192		cterm=none		guifg=#a33470	gui=none
hi Special		ctermfg=194		cterm=none		guifg=#eee7ad	gui=none
hi String		ctermfg=113		cterm=none		guifg=#cfddbc	gui=none
hi Comment		ctermfg=246		cterm=none		guifg=#455c60	gui=none
hi Todo			ctermfg=245		cterm=none		guifg=#8f8f8f	gui=none

" Diffs
hi DiffAdd gui=none guibg=#005500
hi DiffDelete gui=none guibg=#aa0000
hi DiffChange gui=none guibg=#000088

" Links
hi! link FoldColumn		Folded
hi! link CursorColumn	CursorLine

" Breakpoints
hi DbgBreakPt gui=none guifg=#f6f3e8 guibg=#161616
hi DbgCurrent gui=none guifg=#ffaa00 guibg=#161616

" vim:set ts=4 sw=4 noet:
