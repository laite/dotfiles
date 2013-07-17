#/bin/bash

# first we'll check startup arguments
if [ $# -ne 1 ]
then
	echo "$0: Bad arguments!"
    echo "usage: $0 directory"
	exit;
fi

source=$1
# create needed directory to /data/str/Music
new_folder="/data/str/Music/$(echo "$source" | sed 's/\/data\/str\/_Music\///' | sed 's/[^\/]$/&\//')"

mkdir -p "$new_folder"

echo ":: Copying $source to $new_folder"
cp -rav "$source" "$new_folder.." || {
# on failure, abort
echo ":: ABORT - copying did NOT succeed ::"
exit
}

echo ":: Removing original $source"
rm -Ivr "$source"
