#!/bin/sh

echo "Backuping home"
/home/laite/bin/backup_script.sh /home/laite/ /data/backups/home /home/laite/bin/backup_exclude.list 
echo "Backuping Documents"
/home/laite/bin/backup_script.sh /data/str/Documents/ /data/backups/Documents
echo "Backuping workspace"
/home/laite/bin/backup_script.sh /data/str/workspace/ /data/backups/workspace
