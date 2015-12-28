#!/bin/sh

if [ -n "$GDMSESSION" ] && which gdmflexiserver > /dev/null; then
	echo "XScreenSaver.newLoginCommand: gdmflexiserver -ls" | xrdb -merge
fi

if [ -n "$KDE_FULL_SESSION" ] && which kdmctl > /dev/null; then
	echo "XScreenSaver.newLoginCommand: kdmctl reserve" | xrdb -merge
fi

exec xscreensaver "$@"

