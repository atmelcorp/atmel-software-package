# ----------------------------------------------------------------------------
#                  Atmel Microcontroller Software Support
# ----------------------------------------------------------------------------
# Copyright (c) 2017, Atmel Corporation
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following condition is met:
#
# - Redistributions of source code must retain the above copyright notice,
# this list of conditions and the disclaimer below.
#
# Atmel's name may not be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
# DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
# OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# ----------------------------------------------------------------------------

#
# This script generates the target/common/chip_pins_flexcom.h header file from
# the following templates:
# - chip_pins_flexcom.h.header (included as-is)
# - chip_pins_flexcom.h.body (repeated for each flexcom/ioset combination, with
#   FLEXCOMx, IOSx and IOSETx replaced accordingly)
# - chip_pins_flexcom.h.footer (included as-is)

cat chip_pins_flexcom.h.header > chip_pins_flexcom.h
for flexcom in $(seq 0 12) ; do
	for ioset in $(seq 1 4) ; do
		sed -e "s/FLEXCOMx/FLEXCOM$flexcom/g" \
		    -e "s/IOSx/IOS$ioset/g" \
		    -e "s/IOSETx/IOSET$ioset/g" \
		    chip_pins_flexcom.h.body >> chip_pins_flexcom.h
	done
done
cat chip_pins_flexcom.h.footer >> chip_pins_flexcom.h

echo "Header file 'chip_pins_flexcom.h' generated in current directory."
echo "Please review it and move it to target/common/chip_pins_flexcom.h manually."
