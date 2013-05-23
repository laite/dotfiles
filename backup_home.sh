#!/bin/sh
# do incremental backups of directory

MAX_BACKUPS=10

SOURCE_DIR="/home/laite/" # mind the trailing /
TARGET_DIR="/data/backups/home"

# we check differences to latest backup
# (at this point latest backup is still named backup.current, but will get moved to backup.1 by
# the time we get to rsyncing)

# !! WARNING:
# This script relies on LINK_DIR being exactly backup.1, don't change it unless
# you also change rest of the script accordingly (mainly, transitions from current to linkdir 
# and linkdir to first numerical backup dir)
LINK_DIR="$TARGET_DIR/backup.1"

# this is temporary place/name for log file, it gets copied to backup.current in the end
LOG_FILE="$TARGET_DIR/backup.log"

# exclude some directories from syncing, mainly it's a good idea to exclude all caches
# if you don't want to use excludes, delete exclude-from also from $OPTIONS
EXCLUDE_FILE="/home/laite/bin/backup_exclude.list"
# rsync options
# -a archive
# -A preserve ACLs, permissions
# -X preserve extended attributes
# -v be verbose
# -h preserve hard links
# --delete remove extraneous files
OPTIONS="-aAXvh --delete --exclude-from=$EXCLUDE_FILE"

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
echo "*** Backup started $(date '+%A %d.%m.%Y %R')" >> $LOG_FILE
echo "*** Backing up from $SOURCE_DIR to $TARGET_DIR" >> $LOG_FILE
echo "*** Link_dir is set as $LINK_DIR" >> $LOG_FILE
echo "*** Maximum backups: $MAX_BACKUPS" >> $LOG_FILE
echo "*** Excluding following:" >> $LOG_FILE
cat $EXCLUDE_FILE >> $LOG_FILE
START_TIME=$(date +%s)

# execute the backup command
rsync $OPTIONS "$SOURCE_DIR" "$TARGET_DIR/backup.current" >> $LOG_FILE

echo "*** Backup ended $(date '+%A %d.%m.%Y %R')" >> $LOG_FILE
FINISH_TIME=$(date +%s)

# calculate total time
echo "*** Total time: $(( ($FINISH_TIME-$START_TIME) / 60 )) minutes, $(( ($FINISH_TIME-$START_TIME) % 60 )) seconds" >> $LOG_FILE

# leave log on backup folder with current time
mv $LOG_FILE $TARGET_DIR/"backup.current/Backup.log.$(date '+%d.%m.%Y %R')"
