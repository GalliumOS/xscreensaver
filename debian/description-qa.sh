#!/bin/sh

# First, check that all hacks mentioned in debian/control are also
# listed under the same package in split-hacks.config
for PACKAGE in xscreensaver xscreensaver-data xscreensaver-data-extra \
               xscreensaver-gl xscreensaver-gl-extra \
			   xscreensaver-screensaver-bsod \
			   xscreensaver-screensaver-webcollage
do
	# the below sed expression is wonderfully heuristic
	PKGHACKS=`awk '/^Package: '$PACKAGE'$/,/^$/{ print }' < debian/control |
	          sed -ne '/^ [a-z]*,/s/,/ /gp' | sed 's/\.$//'`
	for HACK in `echo $PKGHACKS`
	do
		if ! grep -q "^$HACK	$PACKAGE" debian/split-hacks.config ; then
			echo "Description for $PACKAGE wrongly mentions $HACK"
		fi
	done
done

# Check that all hacks in split-hacks.config are also mentioned in
# debian/control
while read HACK PACKAGE COMMENT
do
	[ -z "$HACK" ] && continue
	[ $HACK != "${HACK#\#}" ] && continue
	grep -q "^ .*$HACK[,.]" debian/control || echo "No mention of $HACK in debian/control"
done < debian/split-hacks.config

exit 0
