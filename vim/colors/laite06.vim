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

let colors_name = "laite06"

" basic view formatting
hi Normal		guifg=#f6f3e8	guibg=#242424	gui=none
hi NonText		guifg=#808080	guibg=#303030	gui=none
hi TabLine    	gui=none guifg=#666666 guibg=#303030
hi TabLineSel   gui=bold guifg=#f6f3e8   guibg=#303030
hi TabLineFill	gui=none guifg=#666666   guibg=#303030

hi FoldColumn	gui=none guifg=#999999 guibg=#f0f0f0
hi SignColumn	gui=none guifg=#999999 guibg=#f0f0f0
hi SignColumn	guifg=#a0a8b0	guibg=#384048	gui=none

hi StatusLine   gui=none guibg=#9899ea guifg=#333333
hi StatusLineNC gui=none guibg=#bbbbbb guifg=white
hi VertSplit    gui=none guibg=#333333 guifg=#999999

" General colors
hi Cursor		guifg=NONE		guibg=#656565	gui=none
hi Visual		guifg=#f6f3e8	guibg=#444444	gui=none
" hi VisualNOS
" hi Search
hi Folded		ctermfg=103		ctermbg=238		cterm=none		guifg=#a0a8b0	guibg=#384048	gui=none
hi Title		ctermfg=7		ctermbg=none	cterm=bold		guifg=#f6f3e8	guibg=NONE		gui=bold
hi StatusLine	ctermfg=7		ctermbg=238		cterm=none		guifg=#f6f3e8	guibg=#444444	gui=none
hi VertSplit	ctermfg=238		ctermbg=238		cterm=none		guifg=#444444	guibg=#444444	gui=none
hi StatusLineNC	ctermfg=243		ctermbg=238		cterm=none		guifg=#857b6f	guibg=#444444	gui=none
hi LineNr		ctermfg=243		ctermbg=0		cterm=none		guifg=#857b6f	guibg=#000000	gui=none
hi SpecialKey	ctermfg=244		ctermbg=236		cterm=none		guifg=#808080	guibg=#343434	gui=none

" Vim >= 7.0 specific colors
if version >= 700
hi CursorLine					ctermbg=236		cterm=none						guibg=#2d2d2d
hi MatchParen	ctermfg=7		ctermbg=243		cterm=bold		guifg=#f6f3e8	guibg=#857b6f	gui=bold
hi Pmenu		ctermfg=7		ctermbg=238						guifg=#f6f3e8	guibg=#444444
hi PmenuSel		ctermfg=0		ctermbg=192						guifg=#000000	guibg=#cae682
endif


" Syntax highlighting
hi Keyword		ctermfg=111		cterm=none		guifg=#f0f0f0	gui=none
hi Statement	ctermfg=111		cterm=none		guifg=#f0f0f0	gui=none
hi Constant		ctermfg=173		cterm=none		guifg=#e5786d	gui=none
hi Number		ctermfg=173		cterm=none		guifg=#e5786d	gui=none
hi PreProc		ctermfg=173		cterm=none		guifg=#e5786d	gui=none
hi Function		ctermfg=192		cterm=none		guifg=#f0f0f0	gui=none
hi Identifier	ctermfg=192		cterm=none		guifg=#f0f0f0	gui=none
hi Type			ctermfg=192		cterm=none		guifg=#a0a8b0	gui=none
hi Special		ctermfg=194		cterm=none		guifg=#77b6aa	gui=none
hi String		ctermfg=113		cterm=none		guifg=#95e454	gui=none
hi Comment		ctermfg=246		cterm=none		guifg=#99968b	gui=none
hi Todo			ctermfg=245		cterm=none		guifg=#8f8f8f	gui=none


" Links
hi! link FoldColumn		Folded
hi! link CursorColumn	CursorLine

" Breakpoints
hi DbgBreakPt gui=none guifg=#f6f3e8 guibg=#161616
hi DbgCurrent gui=none guifg=#ffaa00 guibg=#161616


" vim:set ts=4 sw=4 noet:
