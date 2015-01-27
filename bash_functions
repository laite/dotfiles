# make directory and cd to it instantly
function mkcd() 
{ 
	mkdir "$@" && cd "$@"; 
}

# print contents of directory if it's less than 20 files
function cd()
{
	if [ "$(ls -1 "$*" 2> /dev/null | wc -l)" -lt "20" ]; then
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

function parse_git_branch {
	git branch --no-color 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/\[\1\] /'
}
function curlGET {
	curl -i -X GET $1
}

function curlPOST {
	curl -i -X POST -H 'Content-Type: application/json' -d "$1" $2
}

function curlDELETE {
	curl -i -X DELETE $1
}

function curlPUT {
	curl -i -X PUT -H 'Content-Type: application/json' -d "$1" $2
}
