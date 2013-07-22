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

# find out if there's an artist image in folder
# it should be "folder.jpg" or "folder.png"
topfolder=$(echo "$source" | sed 's#\(/data/str/_Music/[^/]*\).*#\1#')

echo ":: Looking for artist image in $topfolder..."
if [ -f "$topfolder/folder.png" ];
then
	echo -e "${cyan}:: Found artist image! \"$topfolder/folder.png\"${NC}"
	mv -v "$topfolder/folder.png" "$(echo $topfolder | sed 's/_Music/Music/')"
elif [ -f "$topfolder/folder.jpg" ];
then
	echo -e "${cyan}:: Found artist image! \"$topfolder/folder.jpg\"${NC}"
	mv -v "$topfolder/folder.jpg" "$(echo $topfolder | sed 's/_Music/Music/')"
else
	echo ":: No image found."
fi

# remove original folder (with user confirmation)
echo -e "${red}:: Removing original $source${NC}"
rm -Ivr "$source"

# if original topfolder is empty, ask also to remove it
echo ":: $topfolder has still following items"
ls -lA "$topfolder"

if find "$topfolder" -maxdepth 0 -empty | read;
then
	echo -e "${red}:: Removing $topfolder ::${NC}"
	rm -Ivr "$topfolder"
fi
