alias sl='ls'
alias ll='ls -l'
alias la='ls -la'
alias l='ls'
alias lt='ls -lt'

alias cd..='cd ..'
alias ..='cd ..'
alias ...='cd ../..'

alias rawlaunch='rawdog -uw && chromium file:///home/laite/.rawdog/rawdog.html & exit'
alias rawexit='rawdog -uw && exit'
alias :q='exit'
alias d='dict -d wn '

alias torinfo='deluge-console info | egrep "Progress|Name"'
alias find_sub='subberthehut -a -s'

# git
alias g_st='git status'
alias g_co='git commit'
alias g_pu='git push origin master'
alias g_ad='git add'
alias g_di='git diff --color=auto'
alias xclip='xclip -se c'

alias tyc='tty-clock -c -C 3'

alias dirsize='find . -maxdepth 1 -type d -exec du -sh "{}" \;'
alias redtop='python2.7 /home/machina/workspace/git/reddit-top/reddit_top -i 60m'
alias tmux='tmux -2'
