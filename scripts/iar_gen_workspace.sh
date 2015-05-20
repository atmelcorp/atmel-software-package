#!/bin/bash

TEMPLATEFILE=$1
PROJECT_NAME=$2

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

if [ -z $PROJECT_NAME ]
then
    echo PROJECT_NAME not defined 1>&2
    exit 5
fi

sed -e "s%__REPLACE_WORKSPACE_FILE__%\$WS_DIR\$/$PROJECT_NAME.ewp%g" < $TEMPLATEFILE |
    sed -e "s%//%/%g"
