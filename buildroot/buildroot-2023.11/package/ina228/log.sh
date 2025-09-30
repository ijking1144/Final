#!/bin/sh

case "$1" in
	log)
		echo "Logging"
		if [ ! -e /mnt/sdcard/log.txt ]; then
		    touch /mnt/sdcard/log.txt
		fi
		/usr/bin/ina228 >> /mnt/sdcard/log.txt
		;;
	erase)
		echo "erasing logs"
		rm  /mnt/sdcard/log.txt
		;;
	*)
		echo "Usage: $0 {log|erase}"
	exit 1
	;;
esac
exit 0
