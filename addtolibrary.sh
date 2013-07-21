#/bin/bash

cyan='\e[0;36m'
red='\e[1;31m'
NC='\e[0m' # no color

# first we'll check startup arguments
if [ $# -ne 1 ]
then
	echo -e "$0: ${red}Bad arguments!${NC}"
    echo -e "usage: $0 directory"
	exit;
fi

source=$1
# create needed directory to /data/str/Music
new_folder="/data/str/Music/$(echo "$source" | sed 's/\/data\/str\/_Music\///' | sed 's/[^\/]$/&\//')"

mkdir -p "$new_folder"

echo -e "${cyan}:: Copying $source to $new_folder${NC}"
cp -rav "$source" "$new_folder.." || {
# on failure, abort
echo -e "${red}:: ABORT - copying did NOT succeed ::${NC}"
exit
}

echo -e "${cyan}:: Removing original $source${NC}"
rm -Ivr "$source"
