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

