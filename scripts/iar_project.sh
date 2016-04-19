#!/bin/bash
# Generate IAR projects for examples for the available variants

### Arguments parsing
DIR=$1
TOP=$2
BINNAME=$3
TARGET=$4
AVAILABLE_VARIANTS=$5

### Templates
tpl_project="iar_project.template"
tpl_workspace="iar_workspace.template"
tpl_debug="iar_debug.template"

### Global variable
SCRIPTS=$DIR/$TOP/scripts

tpl-split() {
    local template=$1
    local head=$2
    local tail=$3
    local max=`sed -n '$=' $SCRIPTS/${template}`

    echo "SPLIT $template"
    sed -n "1,${head}p" $SCRIPTS/${template} > $DIR/${template}.head
    sed -n "`expr ${head} + 1`, `expr $max - ${tail}`p" $SCRIPTS/${template} > $DIR/${template}.body
    sed "1,`expr $max - ${tail}`d" $SCRIPTS/${template} > $DIR/${template}.tail
}

helper-use-windows-path() {
    local str=${1//\/\//\/}
    echo ${str//\//\\\\}
}

tpl-finalize() {
    local tpl="$1"

    sed -i -e "s/\(__REPLACE_DEP_LIST__\|__REPLACE_PROJECT_FILES__\)//g" "$tpl"
}

tpl-set-prj-files() {
    local tpl=$1
    local section=$2; shift; shift
    local input=$*

    local tmpxml=`mktemp -p "$DIR"`

    (
        for path in ${input}; do
            path=${path//.o/.c}
            path=${path//_gcc.c/_iar.s}

            if [ ! -f $DIR/$TOP/$path ]; then
                echo File $path do not exists! 1>&2
                rm -f "$tmpxml" 2>&1 > /dev/null
                exit 3
            fi

            local win_path=$(helper-use-windows-path $TOP/$path)
            echo -e "  <file><name>\$PROJ_DIR\$\\\\$win_path</name></file>"
        done
    ) > "$tmpxml"

    sed -i -e "/__REPLACE_PROJECT_FILES__/r $tmpxml" "$tpl"

    rm -f "$tmpxml" 2>&1 > /dev/null
}

tpl-set-deps() {
    local tpl="$1"
    local section=$2; shift; shift
    local input=$*
    local empty_group=true
    local tmpxml=`mktemp -p "$DIR"`

    # Read file and fill input array
    (
        echo $path
        for path in ${input}; do
            path=${path//.o/.c}
            path=${path//_gcc.c/_iar.s}

            if [ ! -f $DIR/$TOP/$path ]; then
                echo File $path do not exists! 1>&2
                rm -f "$tmpxml" 2>&1 > /dev/null
                exit 3
            fi

            if [ "$empty_group" = true ]
            then
                empty_group=false
                echo -e "  <group>\n    <name>$section</name>"
            fi

            local win_path=$(helper-use-windows-path $TOP/$path)
            echo -e "    <file><name>\$PROJ_DIR\$\\\\$win_path</name></file>"
        done

        if [ "$empty_group" = false ]
        then
            echo -e "  </group>"
        fi
    ) > "$tmpxml"

    sed -i -e "/__REPLACE_DEP_LIST__/r $tmpxml" "$tpl"

    rm -f "$tmpxml" 2>&1 > /dev/null
}

tpl-set-version() {
    local tpl="$1"
    sed -i -e "s/__REPLACE_VERSION__/$VERSION/g" "$tpl"
}

tpl-finalize() {
    local tpl="$1"

    sed -i "s/\(__REPLACE_DEP_LIST__\|__REPLACE_PROJECT_FILES__\)//g" "$tpl"
}

tpl-set-defines() {
    local tpl="$1"
    local tmpxml=`mktemp -p $DIR`

    for flag in $CFLAGS_DEFS; do
        flag=${flag//:/ }
        echo "          <state>${flag//-D/}</state>"
    done > $tmpxml

    sed -i -e "/__REPLACE_DEFINES__/r $tmpxml" "$tpl"
    sed -i -e "s/__REPLACE_DEFINES__//g" "$tpl"

    rm -f $tmpxml 2>&1 > /dev/null
}

tpl-set-includes() {
    local tpl="$1"
    local tmpxml=`mktemp -p $DIR`

    for include in $CFLAGS_INC; do
        local inc=$(helper-use-windows-path ${include//-I/})
        echo -e "          <state>\$PROJ_DIR\$\\\\$inc</state>"
    done > $tmpxml

    sed -i -e "/__REPLACE_INCLUDES__/r $tmpxml" "$tpl"
    sed -i -e "s/__REPLACE_INCLUDES__//g" "$tpl"

    rm -f $tmpxml 2>&1 > /dev/null
}

tpl-set-linker-script() {
    local tpl="$1"
    local linker_script="$2"

    if [ ! -f $linker_script ]; then
        echo File $linker_script do not exists! 1>&2
        exit 3
    fi

    local win_path=$(helper-use-windows-path $linker_script)
    sed -i -e "s%__REPLACE_LINK_SCRIPT__%\$PROJ_DIR\$\\\\$win_path%g" "$tpl"
}

tpl-set-binary-name() {
    local tpl="$1"
    local binary_name="$2"

    if [ -z $binary_name ]; then
        echo binary_name not defined! 1>&2
        exit 3
    fi

    sed -i -e "s/__REPLACE_BIN_NAME__/$binary_name/g" "$tpl"
}

tpl-set-configuration() {
    local tpl="$1"
    local target=$2
    local variant=$3

    echo "SET target=$target, variant=$variant"
    sed -i "s/__REPLACE_CONF__/$variant/g" "$tpl"
    sed -i "s/__REPLACE_TARGET__/$target/g" "$tpl"
}

tpl-set-soc() {
    local tpl="$1"
    local soc=

    for flag in $CFLAGS_DEFS; do
        if [ "$soc" \< "$(echo $flag | grep CONFIG_SOC_ | sed 's/-DCONFIG_SOC_//')" ]; then
            soc=$(echo $flag | grep CONFIG_SOC_ | sed 's/-DCONFIG_SOC_//')
        fi
    done

    echo "SET SOC=$soc"
    sed -i "s/__REPLACE_SOC__/$soc/g" "$tpl"
}


generate-bodies-ewd() {
    local file="$1"
    local variant=$2
    local tpl=$DIR/${file}_$variant.ewd

    echo "GEN temporary file ${file}_$variant.ewd"

    cat $DIR/iar_debug.template.body > "$tpl"
    local win_path=$(helper-use-windows-path "$iar_debug_script_y")
    sed -i -e "s%__REPLACE_MACFILE__%\$PROJ_DIR\$\\\\$win_path%g" "$tpl"
    sed -i -e "s%//%/%g" "$tpl"

    tpl-set-configuration "$tpl" $TARGET $variant
}

generate-ewd() {
    local file="$1"
    local tpl="$DIR/${file}_$TARGET.ewd"

    tpl-split "$tpl_debug" 4 3

    rm -f $DIR/$file.ewd.bodies
    for variant in $AVAILABLE_VARIANTS; do
        if [ -f $DIR/.env-$variant.sh ]; then
			. $DIR/.env-$variant.sh

            generate-bodies-ewd "$file" $variant
        fi
    done

    # Remove temprary files
    rm -f "$DIR/$file.ewd.bodies"
    touch "$DIR/$file.ewd.bodies"
    for variant in $AVAILABLE_VARIANTS; do
        cat $DIR/${file}_$variant.ewd >> $DIR/$file.ewd.bodies
    done
    rm -f $DIR/${file}_*.ewd

    tpl-set-soc "$DIR/$file.ewd.bodies"

    echo "GEN ${file}_$TARGET.ewd"
    cat $DIR/iar_debug.template.head >  "$tpl"
    cat $DIR/$file.ewd.bodies        >> "$tpl"
    cat $DIR/iar_debug.template.tail >> "$tpl"

    # Clean temporary files
    rm -f $DIR/iar_debug.template.*
    rm -f $DIR/$file.ewd.bodies
}

generate-bodies-ewp() {
    local file="$1"
    local variant="$2"
    local tpl=$DIR/${file}_$variant.ewp

    echo "GEN temporary file ${file}_$variant.ewp"
    cat $DIR/iar_project.template.body > "$tpl"
    tpl-set-defines       "$tpl"
    tpl-set-includes      "$tpl"
    tpl-set-linker-script "$tpl" "$iar_linker_script_y"
    tpl-set-binary-name   "$tpl" "$file"
    tpl-set-configuration "$tpl" $TARGET $variant
}

generate-ewp() {
    local file="$1"
    local tpl="$DIR/${file}_$TARGET.ewp"

    tpl-split "$tpl_project" 4 3

    for variant in $AVAILABLE_VARIANTS; do
        echo "GEN ${file}_$variant.ewp"
        if [ -f $DIR/.env-$variant.sh ]; then
            . $DIR/.env-$variant.sh

            generate-bodies-ewp "$file" $variant
        fi
    done
    # Remove temporary files after merging them
    rm -f "$DIR/$file.ewp.bodies"
    touch "$DIR/$file.ewp.bodies"
    for variant in $AVAILABLE_VARIANTS; do
        cat $DIR/${file}_$variant.ewp >> $DIR/$file.ewp.bodies
    done
    rm -f $DIR/$file_*.ewp

    echo "GEN ${file}_$TARGET.ewp"
    cat $DIR/iar_project.template.head >  "$tpl"
    cat $DIR/$file.ewp.bodies          >> "$tpl"
    cat $DIR/iar_project.template.tail >> "$tpl"
    tpl-set-deps      "$tpl" "target"        "$target_y"
    tpl-set-deps      "$tpl" "utils"         "$utils_y"
    tpl-set-deps      "$tpl" "drivers"       "$drivers_y"
    tpl-set-deps      "$tpl" "lwip"          "$lwip_y"
    tpl-set-deps      "$tpl" "uip"           "$uip_y"
    tpl-set-deps      "$tpl" "usb"           "$usb_y"
    tpl-set-deps      "$tpl" "libsdmmc"      "$libsdmmc_y"
    tpl-set-deps      "$tpl" "libfatfs"      "$libfatfs_y"
    tpl-set-soc       "$tpl"
    tpl-set-prj-files "$tpl" "project_files" "$obj_y"
    tpl-finalize      "$tpl"

    # Remove generated files
    rm -f $DIR/iar_project.template.*
    rm -f $DIR/$file.ewp.bodies
}

generate-eww() {
    local file=$1

    echo "GEN ${file}_$TARGET.eww"
    sed -e "s%__REPLACE_WORKSPACE_FILE__%\$WS_DIR\$/${file}_$TARGET.ewp%g" < "$SCRIPTS/$tpl_workspace" |
        sed -e "s%//%/%g" > "$DIR/${file}_$TARGET.eww"

}

for variant in $AVAILABLE_VARIANTS; do
    make -C $DIR TARGET=$TARGET VARIANT=$variant iar-env
done

generate-ewp $BINNAME
generate-eww $BINNAME
generate-ewd $BINNAME

for variant in $AVAILABLE_VARIANTS; do
    rm -f $DIR/.env-$variant.sh
done

exit 0
