/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2009, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yfuns.h>

//------------------------------------------------------------------------------
/// The function looks for the specified option in the argument array argv.
/// \param option string to find.
/// \param withValue Specifies if the function is used to see if an option 
///                  exists in argv or if the value of the option should be returned
/// \param argc Number of arguments
/// \param argv An array of string pointers.
//------------------------------------------------------------------------------
const char* findOption(char* option, int withValue, int argc, char const* argv[])
{
    int i;
    for (i = 0; i < argc; i++) {
        if (strcmp(option, argv[i]) == 0){
            if (withValue) {
                if (i + 1 < argc) {
                    // The next argument is the value.
                    return argv[i + 1]; 
                }
                else {
                    // The option was found but there is no value to return.
                    return 0; 
                }
            }
            else
            {
                // Return the flag argument itself just to get a non-zero pointer.
                return argv[i]; 
            }
        }
    }
    return 0;
}

//------------------------------------------------------------------------------
// C-SPY will display a message box window with the text given by the msg parameter.
// Text may be split on multiple lines by embedding newlines (\n) in the message string.
// The flash loader execution will halt until the message box OK button is pressed.
//------------------------------------------------------------------------------

void cSpyMessageBox(char* msg)
{
    int log_fd;
    log_fd = __open("$MESSAGE_BOX$", _LLIO_CREAT | _LLIO_TRUNC | _LLIO_WRONLY);
    if (log_fd == -1){
         exit(1);
    }
    __write(log_fd, (unsigned char *)msg, strlen(msg));
    __close(log_fd);
}

//------------------------------------------------------------------------------
// C-SPY will display a message box window with the text given by the msg parameter.
// Text may be split on multiple lines by embedding newlines (\n) in the message string.
// The flash loader execution will halt until the message box OK button is pressed.
// The flash loader will then terminate and notify C-SPY that the flash download failed.
//------------------------------------------------------------------------------

void cSpyFatalError(char* msg)
{
    cSpyMessageBox(msg);
    exit(1);
}

//------------------------------------------------------------------------------
// C-SPY will display a log message given by msg in the debug log window.
// Text may be split on multiple lines by embedding newlines (\n) in the message string.
//------------------------------------------------------------------------------
void cSpyMessageLog(char* msg)
{
    int messageLogFile = -1;
    messageLogFile = __open("$DEBUG_LOG$", _LLIO_CREAT | _LLIO_TRUNC | _LLIO_WRONLY);
    if (messageLogFile == -1) {
        cSpyFatalError("Flash loader failed");
    }
     __write(messageLogFile, (unsigned char *)msg, strlen(msg));
     __close(messageLogFile);
}    



