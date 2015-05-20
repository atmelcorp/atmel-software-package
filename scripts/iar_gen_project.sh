#!/bin/bash

ROOTDIR=$1
DEP_FILE=$2
TEMPLATE_FILE=$3
LINKER_SCRIPT=$4
BINARY_NAME=$5
SERIENAME=$6

# Check script arguments
if [ -z $ROOTDIR ]
then
    echo ROOTDIR is not defined 1>&2
    exit 1
fi

if [ ! -d $ROOTDIR ]
then
    echo $ROOTDIR is not a directory 1>&2
    exit 1
fi

# Other params depends on current directory so we cd to $ROOTDIR before testing them
cd $ROOTDIR

if [ -z $DEP_FILE ]
then
    echo DEP_FILE not defined! 1>&2
    exit 2
fi

if [ ! -f $DEP_FILE ]
then
    echo $DEP_FILE not a regular file 1>&2
    exit 2
fi

if [ -z $TEMPLATE_FILE ]
then
    echo TEMPLATE_FILE not defined! 1>&2
    exit 3
fi

if [ ! -f $TEMPLATE_FILE ]
then
    echo $TEMPLATE_FILE not a regular file 1>&2
    exit 3
fi

if [ -z $LINKER_SCRIPT ]
then
    echo LINKER_SCRIPT not defined 1>&2
    exit 4
fi

if [ -z $BINARY_NAME ]
then
    echo BINARY_NAME not defined 1>&2
    exit 5
fi

if [ -z $SERIENAME ]
then
    echo SERIENAME not defined 1>&2
    exit 5
fi

tmpdepfiles=$(mktemp)
tmpdepxml=$(mktemp)

# Everything fine, let's compute project dependencies (needed *.c files).
cat $DEP_FILE |grep "\(drivers\|target\|utils\).*:\$" |sed -e "s/\.h/\.c/g" |sed -e "s%\(.*\)\(drivers.*\|utils.*\|target.*\)\:\$%\2%g" |xargs -I \{\} bash -c 'if [ -e {} ]; then echo {};fi' > $tmpdepfiles

# Generate the xml tree (source dependencies)
(
    echo -e "<group>\n  <name>drivers</name>"

    for var in drivers/*
    do
	if [ -d $var ];then

	    echo -e "    <group>"
	    echo "      <name>$(basename $var)</name>"
	    grep $tmpdepfiles -e "$var" |sed -e "s|\(.*\)|      <file><name>\$PROJ_DIR\$/../../\1</name></file>|g"
	    find $var -name "*.s" |sed -e "s|\(.*\)|      <file><name>\$PROJ_DIR\$/../../\1</name></file>|g"
	    echo "    </group>"
	fi
    done

    echo "</group>"

    echo -e "<group>\n  <name>target/</name>"

    for var in target/*
    do
	if [ -d $var ];then
	    echo -e "    <group>"
	    echo "      <name>$(basename $var)</name>"
	    grep $tmpdepfiles -e "$var" |sed -e "s|\(.*\)|      <file><name>\$PROJ_DIR\$/../../\1</name></file>|g"
	    find $var -name "*.s" |sed -e "s|\(.*\)|      <file><name>\$PROJ_DIR\$/../../\1</name></file>|g"
	    echo "    </group>"

	fi
    done

    echo "</group>"
    echo "<file>"
    echo "  <name>\$PROJ_DIR\$/main.c</name>"
    echo "</file>"
) > $tmpdepxml

# Left parameters are needed defines to build. Let's make corresponding xml tree
argv=("$@")
for ((i=6;i<$#;i++))
do
    project_defines=$project_defines"<state>${argv[$i]}</state>\n"
done

# Populate the template and send it to stdout
sed -e "/__REPLACE_DEP_LIST__/r $tmpdepxml" < $TEMPLATE_FILE |
    sed -e "s/__REPLACE_DEP_LIST__//g" |
    sed -e "s%__REPLACE_LINK_SCRIPT__%\$PROJ_DIR\$/$LINKER_SCRIPT%g" |
    sed -e "s/__REPLACE_BIN_NAME__/$BINARY_NAME/g" |
    sed -e "s%__REPLACE_DEFINES__%$project_defines%g" |
    sed -e "s/__REPLACE_CHIP_SERIE__/$SERIENAME/g" |
    sed -e "s%//%/%g"

# No need of temp files any more
rm -f $tmpdepxml 2>&1 > /dev/null
rm -f $tmpdepfiles 2>&1 > /dev/null
