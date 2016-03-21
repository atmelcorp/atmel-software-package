#!/bin/bash

SECTION=$1
TEMPLATE_FILE=$2

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

# split template file $1 to 3 parts: header ($2 lines), body, tail(last $3 lines)
function _split_template() {
    local template=$1
    local head=$2
    local tail=$3
    local max=`sed -n '$=' ${template}`

    sed -n "1,${head}p" ${template} > ${template}.head
    sed -n "`expr ${head} + 1`, `expr $max - ${tail}`p" ${template} > ${template}.body
    sed "1,`expr $max - ${tail}`d" ${template} > ${template}.tail
}

function _configuration() {
    sed -e "s/__REPLACE_CONF__/$1/g" < $TEMPLATE_FILE |
        sed -e "s/__REPLACE_BOARD__/$2/g"
}

case $SECTION in
    "split")
        _split_template $TEMPLATE_FILE $3 $4
        ;;
    "configuration")
        _configuration $3 $4
        ;;
esac
