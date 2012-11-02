#temporary solution (until next boot, run as root)
echo N> /sys/module/drm_kms_helper/parameters/poll

#permanent solution (as root)
echo "options drm_kms_helper poll=N">/etc/modprobe.d/local.conf
