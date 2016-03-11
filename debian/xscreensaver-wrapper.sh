#!/bin/sh

if [ -n "$GDMSESSION" ]; then
    case "$XDG_GREETER_DATA_DIR" in
        *lightdm*)
            which dm-tool > /dev/null && echo "XScreenSaver.newLoginCommand: dm-tool switch-to-greeter" | xrdb -merge
            ;;
        *)
            which gdmflexiserver > /dev/null && echo "XScreenSaver.newLoginCommand: gdmflexiserver -ls" | xrdb -merge
            ;;
    esac
fi

if [ -n "$KDE_FULL_SESSION" ] && which kdmctl > /dev/null; then
	echo "XScreenSaver.newLoginCommand: kdmctl reserve" | xrdb -merge
fi

exec xscreensaver "$@"

