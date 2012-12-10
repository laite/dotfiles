" Vim color file
" Maintainer:   laite
" Last Change:  2012 Aug 17

set background=light
hi clear
if exists("syntax_on")
    syntax reset
endif
let g:colors_name="laite04"

hi Cursor       guifg=white guibg=#d8896a

" basic view formatting
hi Normal       gui=none guifg=black   guibg=#f0f0f0
hi NonText      gui=none guifg=#999999 guibg=#dddddd
hi TabLineFill	gui=none guifg=black   guibg=#dddddd
hi LineNr 		gui=none guifg=#999999 guibg=#dddddd 
hi FoldColumn	gui=none guifg=#999999 guibg=#f0f0f0

hi StatusLine   gui=none guibg=#c8c9da guifg=#333333
hi StatusLineNC gui=none guibg=#bbbbbb guifg=white
hi VertSplit    gui=none guibg=#333333 guifg=#999999
hi Folded		gui=none guibg=#dddddd guifg=#999999

" independent items
hi Statement    gui=bold guifg=#222222
hi Type         gui=bold guifg=#222222
hi Special      gui=none guifg=#990055
hi Constant     gui=none guifg=#990055
hi Number		gui=none guifg=#990055
hi Identifier   gui=none guifg=darkcyan
hi Preproc      gui=none guifg=#002a70
hi Comment      gui=none guifg=#999999
hi Title        gui=none guifg=black
hi cppSTL		gui=none guifg=#103a90

hi MatchParen 	gui=none guifg=white guibg=#c0c0c0
hi Visual       gui=none guibg=#ccccfc guifg=black
hi Search       gui=none guibg=#aaffaa guifg=black
hi Directory    gui=none guifg=darkblue
hi WarningMsg   gui=none guifg=red 
hi Error        gui=none guifg=white guibg=red
hi Todo         gui=none guifg=black guibg=yellow

hi MoreMsg      gui=none
hi ModeMsg      gui=none guifg=darkred


hi perlIdentifier			gui=none guifg=black 
hi perlVarPlain				gui=none guifg=#106020 
hi perlVarPlain2			gui=none guifg=#106020 
hi perlFunctionName			gui=none guifg=black 
hi perlArrow				gui=none guifg=black 
hi perlFiledescRead			gui=none guifg=black 
hi perlVarSimpleMember		gui=none guifg=black 
hi perlFiledescStatement	gui=none guifg=black 
hi perlVarNotInMatches		gui=none guifg=black 
hi perlVarSimpleMember		gui=none guifg=black 
hi perlVarSimpleMemberName 	gui=none guifg=#106020 
hi perlVarNotInMatches		gui=none guifg=black 
hi perlVarSlash				gui=none guifg=black 
hi perlFormatName			gui=none guifg=black 
hi perlFunctionName			gui=none guifg=black 
hi perlMethod				gui=none guifg=black 
hi perlFunction				gui=none guifg=#a01300

hi perlStatementControl 	gui=none guifg=#a01300
hi perlStatementMisc	 	gui=none guifg=black
hi perlStatementStorage 	gui=none guifg=#a01300
