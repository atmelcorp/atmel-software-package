#!/bin/bash
# Generate IAR projects for examples for the available variants

set -e

### Arguments parsing
DIR="$1"
TOP="$2"
BINNAME="$3"
TARGET="$4"
AVAILABLE_VARIANTS="$5"
WORKSPACE_TEMPLATE="$6"
PROJECT_TEMPLATE="$7"
DEBUG_TEMPLATE="$8"
IAR_INFO_CENTER_STARTUP_TEMPLATE="$9"
IAR_INFO_CENTER_EXAMPLE_TEMPLATE="${10}"
IAR_INFO_CENTER_EWINFO_TEMPLATE="${11}"

### Global variable
SCRIPTS="$DIR/$TOP/scripts"

tpl-split() {
    local template_src="$1"
    local template="$2"
    local nod="$3"
    local head
    local tail

    echo "SPLIT $template_src"
    head=$(sed -n "/<${nod}>/=" "${template_src}" | sed -n '1p')
    tail=$(sed -n "/<\/${nod}>/=" "${template_src}" | sed -n '$p')
    # head: from start of file to <configuration> (excluded)
    sed -n "1,`expr ${head} - 1`p" "${template_src}" > "$DIR/${template}.head"
    # body: from <configuration> to </configuration> (both included)
    sed -n "${head},${tail}p" "${template_src}" > "$DIR/${template}.body"
    # tail: from </configuration> (excluded) to end of file
    sed -n "`expr ${tail} + 1`,\$p" "${template_src}" > "$DIR/${template}.tail"
}

helper-use-windows-path() {
    local str=${1//\/\//\/}
    echo ${str//\//\\\\}
}

tpl-finalize() {
    local tpl="$1"

    sed -i -e "s/\(__REPLACE_DEP_LIST__\|__REPLACE_PROJECT_FILES__\)//g" "$tpl"
}

find-source() {
    local dir="$1"
    local obj="$2"
    local path=${obj//.o/.c}
    if [ ! -f "$dir/$path" ]; then
        path=${obj//.o/.s}
        if [ ! -f "$dir/$path" ]; then
            echo "Source file for $obj not found!" 1>&2
            exit 3
        fi
    fi
    echo $path
}

tpl-set-prj-files() {
    local tpl="$1"
    local section="$2"; shift; shift
    local input="$*"

    local tmpxml=`mktemp -p "$DIR"`

    (
        for path in ${input}; do
            path=$(find-source "$DIR/$TOP" "$path")
            local win_path=$(helper-use-windows-path "$TOP/$path")
            echo -e "  <file><name>\$PROJ_DIR\$\\\\$win_path</name></file>"
        done
    ) > "$tmpxml"

    sed -i -e "/__REPLACE_PROJECT_FILES__/r $tmpxml" "$tpl"

    rm -f "$tmpxml" 2>&1 > /dev/null
}

tpl-set-deps() {
    local tpl="$1"
    local section="$2"; shift; shift
    local input=$*
    local empty_group=true
    local tmpxml=`mktemp -p "$DIR"`

    # Read file and fill input array
    (
        echo $path
        for path in ${input}; do
            path=$(find-source "$DIR/$TOP" "$path")

            if [ "$empty_group" = true ]
            then
                empty_group=false
                echo -e "  <group>\n    <name>$section</name>"
            fi

            local win_path=$(helper-use-windows-path "$TOP/$path")
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
    local tmpxml=`mktemp -p "$DIR"`

    for flag in $CFLAGS_DEFS; do
        flag=${flag//:/ }
        echo "          <state>${flag//-D/}</state>"
    done > "$tmpxml"

    sed -i -e "/__REPLACE_DEFINES__/r $tmpxml" "$tpl"
    sed -i -e "s/__REPLACE_DEFINES__//g" "$tpl"

    rm -f "$tmpxml" 2>&1 > /dev/null
}

tpl-set-includes() {
    local tpl="$1"
    local tmpxml=`mktemp -p "$DIR"`

    for include in $CFLAGS_INC; do
        local inc=$(helper-use-windows-path "${include//-I/}")
        echo -e "          <state>\$PROJ_DIR\$\\\\$inc</state>"
    done > "$tmpxml"

    sed -i -e "/__REPLACE_INCLUDES__/r $tmpxml" "$tpl"
    sed -i -e "s/__REPLACE_INCLUDES__//g" "$tpl"

    rm -f "$tmpxml" 2>&1 > /dev/null
}

tpl-set-linker-script() {
    local tpl="$1"
    local linker_script="$2"

    if [ ! -f $linker_script ]; then
        echo "File $linker_script not found!" 1>&2
        exit 3
    fi

    local win_path=$(helper-use-windows-path "$linker_script")
    sed -i -e "s%__REPLACE_LINK_SCRIPT__%\$PROJ_DIR\$\\\\$win_path%g" "$tpl"
}

tpl-set-program-entry() {
    local tpl="$1"
    local entry="$2"

    sed -i -e "s%__REPLACE_ENTRY__%$entry%g" "$tpl"
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

tpl-set-chip() {
    local tpl="$1"
    local chip=

    for flag in $CFLAGS_DEFS; do
        if [ "$chip" \< "$(echo $flag | grep CONFIG_CHIP_ | sed 's/-DCONFIG_CHIP_//')" ]; then
            chip=$(echo $flag | grep CONFIG_CHIP_ | sed 's/-DCONFIG_CHIP_/AT/')
            # workaround: IAR uses "AT91" prefix for SAM9xx5 devices and "AT" for SAMA5
            chip=$(echo $chip | sed 's/ATSAM9/AT91SAM9/')
        fi
    done

    echo "SET CHIP=$chip"
    if [ "$chip" = AT91SAM9X60 ]; then
        sed -i "s/__REPLACE_CHIP__/SAM9X60/g" "$tpl"
        # workaround: IAR uses "Microchip" for SAM9X60 device
        sed -i "s/Atmel/Microchip/g" "$tpl"
    else
        sed -i "s/__REPLACE_CHIP__/$chip/g" "$tpl"
    fi
}


generate-bodies-ewd() {
    local file="$1"
    local variant="$2"
    local tpl="$DIR/${file}_$variant.ewd"

    echo "GEN temporary file ${file}_$variant.ewd"

    cat "$DIR/iar_debug.body" > "$tpl"
    local win_path=$(helper-use-windows-path "$iar_debug_script_y")
    sed -i -e "s%__REPLACE_MACFILE__%\$PROJ_DIR\$\\\\$win_path%g" "$tpl"
    sed -i -e "s%//%/%g" "$tpl"

    if [ -n "$iar_flashloader_script_y" ]; then
        sed -i -e "s%__REPLACE_FLASH_LOADER__%1%g" "$tpl"
        local win_path=$(helper-use-windows-path "$iar_flashloader_script_y")
        sed -i -e "s%__REPLACE_FLASH_LOADER_V3__%\$PROJ_DIR\$\\\\$win_path%g" "$tpl"
    fi

    tpl-set-configuration "$tpl" $TARGET $variant

}

generate-ewd() {
    local file="$1"
    local tpl="$DIR/${file}_$TARGET.ewd"

    tpl-split "$DEBUG_TEMPLATE" iar_debug configuration

    rm -f "$DIR/$file.ewd.bodies"
    for variant in $AVAILABLE_VARIANTS; do
        if [ -f "$DIR/.env-$variant.sh" ]; then
            . "$DIR/.env-$variant.sh"
            generate-bodies-ewd "$file" $variant
        fi
    done

    # Remove temprary files
    rm -f "$DIR/$file.ewd.bodies"
    touch "$DIR/$file.ewd.bodies"
    for variant in $AVAILABLE_VARIANTS; do
        cat "$DIR/${file}_$variant.ewd" >> "$DIR/$file.ewd.bodies"
        rm -f "$DIR/${file}_$variant.ewd"
    done

    tpl-set-chip "$DIR/$file.ewd.bodies"

    echo "GEN ${file}_$TARGET.ewd"
    cat "$DIR/iar_debug.head" > "$tpl"
    rm -f "$DIR/iar_debug.head"
    cat "$DIR/$file.ewd.bodies" >> "$tpl"
    rm -f "iar_debug.body"
    rm -f "$DIR/$file.ewd.bodies"
    cat "$DIR/iar_debug.tail" >> "$tpl"
    rm -f "$DIR/iar_debug.tail"
}

generate-bodies-ewp() {
    local file="$1"
    local variant="$2"
    local tpl="$DIR/${file}_$variant.ewp"

    echo "GEN temporary file ${file}_$variant.ewp"
    cat "$DIR/iar_project.body" > "$tpl"
    tpl-set-defines       "$tpl"
    tpl-set-includes      "$tpl"
    tpl-set-linker-script "$tpl" "$iar_linker_script_y"
    tpl-set-program-entry "$tpl" "$iar_program_entry_y"
    tpl-set-binary-name   "$tpl" "$file"
    tpl-set-configuration "$tpl" $TARGET $variant
}

generate-ewp() {
    local file="$1"
    local tpl="$DIR/${file}_$TARGET.ewp"

    tpl-split "$PROJECT_TEMPLATE" iar_project configuration

    for variant in $AVAILABLE_VARIANTS; do
        echo "GEN ${file}_$variant.ewp"
        if [ -f "$DIR/.env-$variant.sh" ]; then
            . "$DIR/.env-$variant.sh"
            generate-bodies-ewp "$file" $variant
        fi
    done
    # Remove temporary files after merging them
    rm -f "$DIR/$file.ewp.bodies"
    touch "$DIR/$file.ewp.bodies"
    for variant in $AVAILABLE_VARIANTS; do
        cat "$DIR/${file}_$variant.ewp" >> "$DIR/$file.ewp.bodies"
        rm -f "$DIR/${file}_$variant.ewp"
    done

    echo "GEN ${file}_$TARGET.ewp"
    cat "$DIR/iar_project.head" > "$tpl"
    rm -f "$DIR/iar_project.head"
    cat "$DIR/$file.ewp.bodies" >> "$tpl"
    rm -f "$DIR/iar_project.body"
    rm -f "$DIR/$file.ewp.bodies"
    cat "$DIR/iar_project.tail" >> "$tpl"
    rm -f "$DIR/iar_project.tail"

    tpl-set-deps      "$tpl" "target"        "$target_y"
    tpl-set-deps      "$tpl" "utils"         "$utils_y"
    tpl-set-deps      "$tpl" "arch"          "$arch_y"
    tpl-set-deps      "$tpl" "drivers"       "$drivers_y"
    tpl-set-deps      "$tpl" "lwip"          "$lwip_y"
    tpl-set-deps      "$tpl" "uip"           "$uip_y"
    tpl-set-deps      "$tpl" "usb"           "$usb_y"
    tpl-set-deps      "$tpl" "libsdmmc"      "$libsdmmc_y"
    tpl-set-deps      "$tpl" "libfatfs"      "$libfatfs_y"
    tpl-set-deps      "$tpl" "freertos"      "$libfreertos_y"
    tpl-set-chip      "$tpl"
    tpl-set-prj-files "$tpl" "project_files" "$obj_y"
    tpl-finalize      "$tpl"
}


generate-bodies-eww() {
    local file="$1"
    local target="$2"
    local tpl="$DIR/iar_workspace_$target.eww"

    echo "GEN temporary file iar_workspace_$target.eww"
    cat "$file" > "$tpl"
}

generate-eww() {
    local file=$1
    local tpl="$DIR/${file}.eww"

    if [ -f "$DIR/${file}.eww" ]; then
       echo "UPD ${file}.eww"
       tpl-split "$WORKSPACE_TEMPLATE" iar_workspace project
       generate-bodies-eww "$DIR/iar_workspace.body" $TARGET
       rm -f "$DIR/iar_workspace.head"
       rm -f "$DIR/iar_workspace.body"
       rm -f "$DIR/iar_workspace.tail"

       tpl-split "$tpl" iar_workspace project
       cat "$DIR/iar_workspace.head" > "$tpl"
       rm -f "$DIR/iar_workspace.head"
       cat "$DIR/iar_workspace.body" >> "$tpl"
       sed -i "s%__REPLACE_WORKSPACE_FILE__%\$WS_DIR\$/${file}_$TARGET.ewp%g" "$DIR/iar_workspace_$TARGET.eww"
       cat "$DIR/iar_workspace_$TARGET.eww" >> "$tpl"
       rm -f "$DIR/iar_workspace.body"
       rm -f "$DIR/iar_workspace_$TARGET.eww"
       cat "$DIR/iar_workspace.tail" >> "$tpl"
       rm -f "$DIR/iar_workspace.tail"

    else
       echo "GEN ${file}_$TARGET.eww"
       sed -e "s%__REPLACE_WORKSPACE_FILE__%\$WS_DIR\$/${file}_$TARGET.ewp%g" < "$WORKSPACE_TEMPLATE" |
       sed -e "s%//%/%g" > "$DIR/${file}.eww"
    fi
}

generate-infocenter() {
    local tpl="$DIR/main.c"
    #local tp2="$DIR/main.purpose"
    local main_purpose=`mktemp -p "$DIR"`
    local main_desc=`mktemp -p "$DIR"`
    #local tp3="$DIR/main.desc"
    local tp4="$DIR/StartupScreen.ewsample"
    local tp5="$DIR/ExampleInfo.ENU.xml"
    local tp6="$DIR/ewinfo.ENU.html"

    if [ ! -f "$tp4" -a -e "$tpl" ]; then
        cat "$IAR_INFO_CENTER_STARTUP_TEMPLATE" > "$tp4"
        sed -n '/section Purpose/,/section Requirements$/p' $tpl | grep -Ev '(section Purpose|section Requirements$)' | cut -f 1,2 >$main_purpose
        sed -i '/^$/d' $main_purpose
        sed -i 's/\ \*//g' $main_purpose

        sed -n '/section Description/,/section Usage$/p' $tpl | grep -Ev '(section Description|section Usage$)' | cut -f 1,2 >$main_desc
        sed -i '/^$/d' $main_desc
        sed -i 's/\ \*//g' $main_desc
        cat "$IAR_INFO_CENTER_EXAMPLE_TEMPLATE" > "$tp5"

        sed -i "s/__REPLACE_EXAMPLE_NAME__/$BINNAME/g" "$tp5"
        sed -i "/<iar_description>/r $main_purpose" "$tp5"
        cat "$IAR_INFO_CENTER_EWINFO_TEMPLATE" > "$tp6"
        sed -i "/Description:/r $main_desc" "$tp6"
    fi
    rm -f "$main_purpose"
    rm -f "$main_desc"
}

for variant in $AVAILABLE_VARIANTS; do
    make -C "$DIR" TARGET=$TARGET VARIANT=$variant iar-env
done

generate-ewp $BINNAME
generate-eww $BINNAME
generate-ewd $BINNAME

generate-infocenter

for variant in $AVAILABLE_VARIANTS; do
    rm -f "$DIR/.env-$variant.sh"
done

exit 0
