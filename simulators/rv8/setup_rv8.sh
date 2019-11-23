#!/bin/sh

if [ $# -eq 0 ]; then
	echo 'Please input the path to the rv8 image .gz file'
	exit
fi

has() { type "$1" &> /dev/null; }
if has "docker"; then
	if has "zcat"; then
		zcat $1 | docker import - rv8
	fi
else
	echo "Please install docker using 'pacman -S docker'"
	exit
fi
