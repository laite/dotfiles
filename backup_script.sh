#!/bin/sh
# do incremental backups of directory


# first we'll check startup arguments
if [ $# -lt 2 ] || [ $# -gt 3 ]
then
	echo "$0: Bad arguments!"
    echo "usage: $0 source_dir target_dir [exclude_file]"
	exit;
fi


SOURCE_DIR="$1"
TARGET_DIR="$2"

# exclude some directories from syncing, mainly it's a good idea to exclude all caches
# note that exclude file is optional
EXCLUDE_COMMAND=""
if [ $# -eq 3 ]
then
	EXCLUDE_FILE="$3"
	EXCLUDE_COMMAND="--exclude-from=$3"
fi

# number of last kept backup directory
MAX_BACKUPS=10

# this is temporary place/name for log file, it gets copied to backup.current in the end
LOG_FILE="$TARGET_DIR/backup.log"
echo "*** Starting to run $0 ***" >> $LOG_FILE
echo "*** It's now $(date '+%A %d.%m.%Y %R')" >> $LOG_FILE

# we check differences to latest backup
# (at this point latest backup is still named backup.current, but will get moved to backup.1 by
# the time we get to rsyncing)

# !! WARNING:
# This script relies on LINK_DIR being exactly backup.1, don't change it unless
# you also change rest of the script accordingly (mainly, transitions from current to linkdir 
# and linkdir to first numerical backup dir)
LINK_DIR="$TARGET_DIR/backup.1"
LINK_COMMAND="--link-dest=$LINK_DIR"

# if there is no backup.current directory we don't link to anything, and create a warning
if [[ ! -d "$TARGET_DIR/backup.current" ]]; then
		LINK_COMMAND=""
		echo "*** WARNING: There is no backup.current - directory in $TARGET_DIR ***" >> $LOG_FILE
		echo "*** If you are running the script for the first time, this is expected ***" >> $LOG_FILE
fi


# rsync options
# -a archive
# -A preserve ACLs, permissions
# -X preserve extended attributes
# -v be verbose
# -h preserve hard links
# --delete remove extraneous files
# --exclude-from read excluded files/folders from a file

# if we are initing backups we don't yet have link-dest
OPTIONS="-aAXvh --delete $EXCLUDE_COMMAND $LINK_COMMAND"

# remove previous MAX_BACKUP folder if it exists
if [ -d $TARGET_DIR/backup.$MAX_BACKUPS ]
then
	rm -rf $TARGET_DIR/backup.$MAX_BACKUPS
	echo "removed $TARGET_DIR/backup.$MAX_BACKUPS" >> $LOG_FILE
fi

# move previous backups further up
for (( c=$MAX_BACKUPS; c>=1; c-- ))
do
	if [ -d $TARGET_DIR/backup.$c ]
	then
		new_id=$c
		(( new_id++ ))
		mv "$TARGET_DIR/backup.$c" "$TARGET_DIR/backup.$new_id"
	fi
done

# mv also 'current' to '1'
if [ -d $TARGET_DIR/backup.current ]
then
	mv "$TARGET_DIR/backup.current" "$TARGET_DIR/backup.1"
fi

# start actually backing up

# Log some information
echo "*** Backing up from $SOURCE_DIR to $TARGET_DIR" >> $LOG_FILE
echo "*** Link_dir is set as $LINK_DIR" >> $LOG_FILE
echo "*** Maximum backups: $MAX_BACKUPS" >> $LOG_FILE
if [ ! "$EXCLUDE_COMMAND" == "" ]
then
	echo "*** Excluding following:" >> $LOG_FILE
	cat $EXCLUDE_FILE >> $LOG_FILE
fi
START_TIME=$(date +%s)

# execute the backup command
rsync $OPTIONS "$SOURCE_DIR" "$TARGET_DIR/backup.current" >> $LOG_FILE

echo "*** Backup ended $(date '+%A %d.%m.%Y %R')" >> $LOG_FILE
FINISH_TIME=$(date +%s)

# calculate total time
echo "*** Total time: $(( ($FINISH_TIME-$START_TIME) / 60 )) minutes, $(( ($FINISH_TIME-$START_TIME) % 60 )) seconds" >> $LOG_FILE

# leave log on backup folder with current time
mv $LOG_FILE $TARGET_DIR/"backup.current/Backup.log.$(date '+%d.%m.%Y %R')"
