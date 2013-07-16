# make directory and cd to it instantly
function mkcd() 
{ 
	mkdir "$@" && cd "$@"; 
}

# print contents of directory if it's less than 20 files
function cd()
{
	if [ "$(ls -1 "$*" | wc -l)" -lt "20" ]; then
		builtin cd "$*" && ls
	else
		builtin cd "$*"
	fi
}

# color up man pages
man() {
    env LESS_TERMCAP_mb=$(printf "\e[0;36m") \
	LESS_TERMCAP_md=$(printf "\e[0;36m") \
	LESS_TERMCAP_me=$(printf "\e[0m") \
	LESS_TERMCAP_se=$(printf "\e[0m") \
	LESS_TERMCAP_so=$(printf "\e[1;44;37m") \
	LESS_TERMCAP_ue=$(printf "\e[0m") \
	LESS_TERMCAP_us=$(printf "\e[0;33m") \
	man "$@"
}
