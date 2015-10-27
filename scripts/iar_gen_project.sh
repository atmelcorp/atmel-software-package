#!/bin/bash

SECTION=$1
TEMPLATE_FILE=$2
LIB_NAME=$3
LINKER_SCRIPT=$3
BINARY_NAME=$3
SERIENAME=$3
VERSION=$3

if [ -z $SECTION ]
then
    echo SECTION not defined! 1>&2
    exit 1
fi

if [ -z $TEMPLATE_FILE ]
then
    echo TEMPLATE_FILE not defined! 1>&2
    exit 2
fi

if [ ! -f $TEMPLATE_FILE ]
then
    echo $TEMPLATE_FILE not a regular file 1>&2
    exit 2
fi

function _to_win_path() {
    local str=${1//\/\//\/}
    echo ${str//\//\\\\}
}

function _insert_deps() {
    local section=$1
    local input=()
    local empty_group=true
    local tmpxml=$(mktemp)

    while read -r line
    do
        input+=($line)
    done

    (
        for path in ${input[@]}
        do
            path=${path//.o/.c}
            path=${path//_gcc.c/_iar.s}

            if [ ! -f $path ]
            then
                echo File $path do not exists! 1>&2
                rm -f $tmpxml 2>&1 > /dev/null
                exit 3
            fi

            if [ "$empty_group" = true ]
            then
                empty_group=false
                echo -e "  <group>\n    <name>$section</name>"
            fi

            local win_path=$(_to_win_path $path)
            echo -e "    <file><name>\$PROJ_DIR\$\\$win_path</name></file>"
        done

        if [ "$empty_group" = false ]
        then
            echo -e "  </group>"
        fi
    ) > $tmpxml

    sed -e "/__REPLACE_DEP_LIST__/r $tmpxml" < $TEMPLATE_FILE

    rm -f $tmpxml 2>&1 > /dev/null
}

function _insert_defines() {
    local input=()
    local tmpxml=$(mktemp)

    sed -e 's/-D/:/g' -e 's/$/:/' | while read -d: -r line
    do
        if test -n "$line" ; then
            echo -e "          <state>$line</state>"
        fi
    done > $tmpxml

    sed -e "/__REPLACE_DEFINES__/r $tmpxml" < $TEMPLATE_FILE |
        sed -e "s/__REPLACE_DEFINES__//g"

    rm -f $tmpxml 2>&1 > /dev/null
}

function _insert_includes() {
    local input=()
    local tmpxml=$(mktemp)

    sed -e 's/-I/:/g' -e 's,/,\\,g' -e 's/$/:/' | while read -d: -r line
    do
        if test -n "$line" ; then
            echo "          <state>\$PROJ_DIR\$\\$line</state>"
        fi
    done > $tmpxml

    sed -e "/__REPLACE_INCLUDES__/r $tmpxml" < $TEMPLATE_FILE |
        sed -e "s/__REPLACE_INCLUDES__//g"

    rm -f $tmpxml 2>&1 > /dev/null
}

function _insert_chip_serie_name() {
    local chip_serie=$1

    sed -e "s/__REPLACE_CHIP_SERIE__/$chip_serie/g" < $TEMPLATE_FILE
}

function _insert_linker_script() {
    local linker_script=$1

    if [ ! -f $linker_script ]
    then
        echo File $linker_script do not exists! 1>&2
        exit 3
    fi

    local win_path=$(_to_win_path $linker_script)

    sed -e "s%__REPLACE_LINK_SCRIPT__%\$PROJ_DIR\$\\\\$win_path%g" < $TEMPLATE_FILE
}

function _insert_bin_name() {
    local binary_name=$1

    if [ -z $binary_name ]
    then
        echo binary_name not defined! 1>&2
        exit 3
    fi

    sed -e "s/__REPLACE_BIN_NAME__/$binary_name/g" < $TEMPLATE_FILE
}

function _insert_project_files() {
    local input=()
    local tmpxml=$(mktemp)

    local section=$1

    local input=()

    while read -r line
    do
        input+=($line)
    done

    local tmpxml=$(mktemp)

    (
        for path in ${input[@]}
        do
            path=${path//.o/.c}
            path=${path//_gcc.c/_iar.s}

            if [ ! -f $path ]
            then
                echo File $path do not exists! 1>&2
                rm -f $tmpxml 2>&1 > /dev/null
                exit 3
            fi

            local win_path=$(_to_win_path $path)
            echo -e "  <file><name>\$PROJ_DIR\$\\$win_path</name></file>"
        done
    ) > $tmpxml

    sed -e "/__REPLACE_PROJECT_FILES__/r $tmpxml" < $TEMPLATE_FILE

    rm -f $tmpxml 2>&1 > /dev/null
}

function _finalize() {
    sed -e "s/\(__REPLACE_DEP_LIST__\|__REPLACE_PROJECT_FILES__\)//g" < $TEMPLATE_FILE
}

function _version() {
    sed -e "s/__REPLACE_VERSION__/$VERSION/g" < $TEMPLATE_FILE
}

case $SECTION in
    "lib")
        _insert_deps $LIB_NAME
        ;;
    "definitions")
        _insert_defines
        ;;
    "includes")
        _insert_includes
        ;;
    "binary")
        _insert_bin_name $BINARY_NAME
        ;;
    "linker")
        _insert_linker_script $LINKER_SCRIPT
        ;;
    "chip_serie")
        _insert_chip_serie_name $3
        ;;
    "project_files")
        _insert_project_files
        ;;
    "finalize")
        _finalize
        ;;
    "version")
        _version
        ;;
esac
