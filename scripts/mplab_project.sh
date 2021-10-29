#!/bin/bash
# Generate MPLAB X projects for examples for the available variants

set -e

### Arguments parsing
DIR="$1"
TOP="$2"
BINNAME="$3"
TARGET="$4"
AVAILABLE_VARIANTS="$5"
PROJECT_TEMPLATE="$6"
CONFIGURATION_TEMPLATE="$7"
DEBUG_TEMPLATE="$8"

### Global variable
SCRIPTS="$DIR/$TOP/scripts"
folder_idx=1
TOOLCHAINS="ARM XC32"

tpl-split() {
    local template_src="$1"
    local template="$2"
    local nod="$3"
    local head
    local tail

    echo "SPLIT $template_src"
    echo $*
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
        path=${obj//.o/.S}
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
            echo -e "      <itemPath>../../../$path</itemPath>"
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
        for path in ${input}; do
            path=$(find-source "$DIR/$TOP" "$path")

            if [ "$empty_group" = true ]
            then
                empty_group=false
                echo -e "  <logicalFolder name=\"$section\" displayName=\"$section\" projectFiles=\"true\">"
            fi

            echo -e "    <itemPath>../../../$path</itemPath>"
        done

        if [ "$empty_group" = false ]
        then
            echo -e "  </logicalFolder>"
        fi
    ) > "$tmpxml"

    sed -i -e "/__REPLACE_PROJECT_FILES__/r $tmpxml" "$tpl"

    rm -f "$tmpxml" 2>&1 > /dev/null
}

tpl-set-version() {
    local tpl="$1"
    sed -i -e "s/__REPLACE_VERSION__/$VERSION/g" "$tpl"
}

tpl-set-defines() {
    local tpl="$1"
    local tmpxml=`mktemp -p "$DIR"`
    echo -n "          value=\"" > "$tmpxml"
    for flag in $CFLAGS_DEFS; do
        flag=${flag//:/ }
        echo -n "${flag//-D/};"
    done >> "$tmpxml"
    echo -n "\"" >> "$tmpxml"

    sed -i -e "/__REPLACE_DEFINES__/r $tmpxml" "$tpl"
    sed -i -e "s/__REPLACE_DEFINES__//g" "$tpl"

    rm -f "$tmpxml" 2>&1 > /dev/null
}

tpl-set-includes() {
    local tpl="$1"
    local tmpxml=`mktemp -p "$DIR"`

    echo -n "        <property key=\"common-include-directories\" value=\"" > "$tmpxml"
    for include in $CFLAGS_INC; do
        local inc=$(helper-use-windows-path "${include//-I/}")
        echo -n -e "..\\$inc;"
    done >> "$tmpxml"
    echo "\"/>" >> "$tmpxml"
    sed -i -e "/__REPLACE_INCLUDES__/r $tmpxml" "$tpl"
    sed -i -e "s/__REPLACE_INCLUDES__//g" "$tpl"

    rm -f "$tmpxml" 2>&1 > /dev/null
}

tpl-set-linker-script() {
    local tpl="$1"
    local tmpxml=`mktemp -p "$DIR"`
    local script_path=""

    for toolchain in ${TOOLCHAINS}; do
        if [ $toolchain = "XC32" ]; then
            script_path=$xc32_linker_script_y
        elif [ $toolchain = "ARM" ]; then
            script_path=${gnu_linker_script_y%/*}/
        else
            echo "Compiler Toolchain $toolchain is not supported!" 1>&2
            exit 3
        fi
        echo "<logicalFolder name=\"LinkerScript_${toolchain}\" displayName=\"${toolchain}\" projectFiles=\"true\">" >> $tmpxml
        for linker_script in ${script_path}; do
            for variant in $AVAILABLE_VARIANTS; do
                if [ ! -f $linker_script$variant.ld ]; then
                    echo "File $linker_script$variant.ld not found!" 1>&2
                    exit 3
                fi
                echo "<itemPath>../$linker_script$variant.ld</itemPath>" >> $tmpxml
            done
         done
         echo "</logicalFolder>" >> $tmpxml
    done
    sed -i -e "/__REPLACE_LINK_SCRIPT__/r $tmpxml" "$tpl"
    sed -i -e "s/__REPLACE_LINK_SCRIPT__//g" "$tpl"

    rm -f "$tmpxml" 2>&1 > /dev/null
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
    sed -i "s/<conf>/<conf /g" "$tpl"
    sed -i "s/__REPLACE_CONF__/$variant/g" "$tpl"
    sed -i "s/__REPLACE_TARGET__/$target/g" "$tpl"
}

tpl-set-chip() {
    local tpl="$1"
    local chip=

    for flag in $CFLAGS_DEFS; do
        if [ "$chip" \< "$(echo $flag | grep CONFIG_CHIP_ | sed 's/-DCONFIG_CHIP_//')" ]; then
            chip=$(echo $flag | grep CONFIG_CHIP_ | sed 's/-DCONFIG_CHIP_/AT/')
        fi
    done

    echo "SET CHIP=$chip"
    if [ "$chip" = ATSAM9X60 ]; then
        sed -i "s/__REPLACE_CHIP__/SAM9X60/g" "$tpl"
        sed -i "s/__REPLACE_DFP__/<pack name=\"SAM9X6_DFP\" vendor=\"Microchip\" version=\"1.7.85\"\/>/g" "$tpl"
        sed -i "s/__REPLACE_ADDITIONAL_OPT__/\n        <appendMe value=\"-mfloat-abi=soft\"\/>/g" "$tpl"
    elif [ "$chip" = ATSAMA5D27 ]; then
        sed -i "s/__REPLACE_CHIP__/$chip/g" "$tpl"
        sed -i "s/__REPLACE_DFP__/<pack name=\"SAMA5D2_DFP\" vendor=\"Microchip\" version=\"1.9.106\"\/>/g" "$tpl"
        sed -i "s/__REPLACE_ADDITIONAL_OPT__/\n        <appendMe value=\"-mfloat-abi=hard\"\/>/g" "$tpl"
    fi
}

generate-bodies-conf() {
    local file="$1"
    local variant="$2"

    for toolchain in ${TOOLCHAINS}; do
        local tpl="$DIR/${file}_${variant}_${toolchain}.conf"

        echo "GEN temporary file ${file}_${variant}_${toolchain}.conf"
        cat "$DIR/mplab_conf.body" > "$tpl"
        tpl-set-defines       "$tpl" ${variant} ${toolchain}
        tpl-set-includes      "$tpl"
        tpl-set-configuration "$tpl" $TARGET ${variant}_${toolchain}

        local tmpxml=`mktemp -p "$DIR"`
        if [ $toolchain = "XC32" ]; then
            for var in $AVAILABLE_VARIANTS; do
                if [ ! $var = $variant ]; then
                    echo "<item path=\"../${xc32_linker_script_y}$var.ld\" ex=\"true\" overriding=\"false\"></item>" >> $tmpxml
                fi
                echo "<item path=\"../${gnu_linker_script_y%/*}/$var.ld\" ex=\"true\" overriding=\"false\"></item>" >> $tmpxml
            done
            for path in ${startup_ARM}; do
                path=$(find-source "$DIR/$TOP" "$path")
                echo "<item path=\"../../../$path\" ex=\"true\" overriding=\"false\"></item>" >> $tmpxml
            done
            sed -i -e "s/__REPLACE_TOOLCHAIN_VERSION__//g" "$tpl"
        elif [ $toolchain = "ARM" ]; then
            for var in $AVAILABLE_VARIANTS; do
                if [ ! $var = $variant ]; then
                    echo "<item path=\"../${gnu_linker_script_y%/*}/$var.ld\" ex=\"true\" overriding=\"false\"></item>" >> $tmpxml
                fi
                echo "<item path=\"../$xc32_linker_script_y$var.ld\" ex=\"true\" overriding=\"false\"></item>" >> $tmpxml
            done
            for path in ${startup_XC32}; do
                path=$(find-source "$DIR/$TOP" "$path")
                echo "<item path=\"../../../$path\" ex=\"true\" overriding=\"false\"></item>" >> $tmpxml
            done
            sed -i -e "s/__REPLACE_TOOLCHAIN_VERSION__/10.2.1/g" "$tpl"
        else
            echo "Compiler Toolchain $toolchain is not supported!" 1>&2
            exit 3
        fi
        sed -i -e "s/__REPLACE_TOOLCHAIN__/$toolchain/g" "$tpl"
        sed -i -e "/__REPLACE_LINK_SCRIPT_EX__/r $tmpxml" "$tpl"
        sed -i -e "s/__REPLACE_LINK_SCRIPT_EX__//g" "$tpl"
        if [ $variant = "sram" ]; then
            sed -i -e "s/__REPLACE_BOOTSTRAP_USE__/false/g" "$tpl"
            sed -i -e "s/__REPLACE_BOOTSTRAP_PATH__//g" "$tpl"
        else
            sed -i -e "s/__REPLACE_BOOTSTRAP_USE__/true/g" "$tpl"
            sed -i -e "s/__REPLACE_BOOTSTRAP_PATH__/\${ProjectDir}\/..\/..\/..\/flash_loaders\/mplab\/${TARGET}\/at91bootstrap.elf/g" "$tpl"
        fi

        rm -f "$tmpxml" 2>&1 > /dev/null
    done
}

generate-conf() {
    local file="$1"
    local tpl="$DIR/${TARGET}.X/nbproject/configurations.xml"

    if [ ! -e "$DIR/${TARGET}.X/nbproject" ]; then
        mkdir -p "$DIR/${TARGET}.X/nbproject"
    fi

    cp $CONFIGURATION_TEMPLATE $tpl

    tpl-split "$CONFIGURATION_TEMPLATE" mplab_conf conf

    for variant in $AVAILABLE_VARIANTS; do
        if [ -f "$DIR/.mplab-$variant.sh" ]; then
            . "$DIR/.mplab-$variant.sh"
            generate-bodies-conf "$file" $variant
        fi
    done
    # Remove temporary files after merging them
    rm -f "$DIR/$file.conf.bodies"
    touch "$DIR/$file.conf.bodies"
    for variant in ${AVAILABLE_VARIANTS}; do
        for toolchain in ${TOOLCHAINS}; do
            cat "$DIR/${file}_${variant}_${toolchain}.conf" >> "$DIR/$file.conf.bodies"
            rm -f "$DIR/${file}_${variant}_${toolchain}.conf"
        done
     done

    echo "GEN ${file}_$TARGET.conf"
    cat "$DIR/mplab_conf.head" > "$tpl"
    rm -f "$DIR/mplab_conf.head"
    cat "$DIR/$file.conf.bodies" >> "$tpl"
    rm -f "$DIR/mplab_conf.body"
    rm -f "$DIR/$file.conf.bodies"
    cat "$DIR/mplab_conf.tail" >> "$tpl"
    rm -f "$DIR/mplab_conf.tail"

    tpl-set-linker-script "$tpl"

    tpl-set-deps      "$tpl" "utils"         "$utils_y"
    tpl-set-deps      "$tpl" "usb"           "$usb_y"
    tpl-set-deps      "$tpl" "uip"           "$uip_y"
    tpl-set-deps      "$tpl" "target"        "$target_y"
    tpl-set-deps      "$tpl" "startup_ARM"   "$startup_ARM"
    tpl-set-deps      "$tpl" "startup_XC32"  "$startup_XC32"
    tpl-set-deps      "$tpl" "lwip"          "$lwip_y"
    tpl-set-deps      "$tpl" "libsdmmc"      "$libsdmmc_y"
    tpl-set-deps      "$tpl" "libfatfs"      "$libfatfs_y"
    tpl-set-deps      "$tpl" "freertos"      "$libfreertos_y"
    tpl-set-deps      "$tpl" "drivers"       "$drivers_y"
    tpl-set-deps      "$tpl" "arch"          "$arch_y"
    tpl-set-chip      "$tpl"
    tpl-set-prj-files "$tpl" "project_files" "$obj_y"
    tpl-finalize      "$tpl"
    sed -i -e "s%__REPLACE_PROJRCT__%${file}_$TARGET%g" $tpl
}


generate-project() {
    local file=$1

    if [ ! -e "$DIR/${TARGET}.X/nbproject" ]; then
        mkdir -p "$DIR/${TARGET}.X/nbproject"
    fi

    echo "GEN project.xml"
    sed -e "s%__REPLACE_PROJRCT__%${file}_$TARGET%g" < "$PROJECT_TEMPLATE" |
    sed -e "s%/%/%g" > "$DIR/${TARGET}.X/nbproject/project.xml"
}

for variant in $AVAILABLE_VARIANTS; do
    make -C "$DIR" TARGET=$TARGET VARIANT=$variant mplab-env
done

generate-project $BINNAME
generate-conf $BINNAME

cp -p ../../scripts/mplab_Makefile.template $DIR/${TARGET}.X/Makefile

for variant in $AVAILABLE_VARIANTS; do
    rm -f "$DIR/.mplab-$variant.sh"
done

exit 0
