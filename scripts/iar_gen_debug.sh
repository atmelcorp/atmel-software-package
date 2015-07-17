#!/bin/bash

TEMPLATEFILE=$1
DEBUGSCRIPT=$2

# Check script arguments

if [ -z $TEMPLATEFILE ]
then
    echo ROOTDIR is not defined 1>&2
    exit 1
fi

if [ ! -f $TEMPLATEFILE ]
then
    echo $TEMPLATEFILE is not a regular file 1>&2
    exit 1
fi

if [ -z $DEBUGSCRIPT ]
then
    echo DEBUGSCRIPT is not defined 1>&2
    exit 1
fi

if [ ! -f $DEBUGSCRIPT ]
then
    echo $DEBUGSCRIPT is not a regular file 1>&2
    exit 1
fi

sed -e "s%__REPLACE_MACFILE__%\$PROJ_DIR\$/$DEBUGSCRIPT%g" < $TEMPLATEFILE |
    sed -e "s%//%/%g"
