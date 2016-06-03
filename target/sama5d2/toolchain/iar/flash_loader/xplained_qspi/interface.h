
//
// Argument functions.
//

// The function looks for the specified option in the argument array argv.
// The with_value parameter specifies if the function is used to see if an option
// exists in argv or if the value of the option should be returned. The value
// of an option is the next argument after the matching argument in argv.
// Set with_value to 0 when checking for a flag option like --small_ram.
// Set with_value to 1 when checking for an option with value like --speed 14600.
// The argc parameter is the number of arguments in the argv array.
// The argv parameter is an array of string pointers.
// The argc/argv parameters in FlashDriverInitialize() can be used directly
// when calling this function.
// The function returns a null pointer if the option is not found in argv.
// The function returns a pointer to the argument after the matching option if with_value is set to 1.
// The function returns a pointer to the entry in argv that matches the option if with_value is set to 0.

const char* findOption(char* option, int withValue, int argc, char const* argv[]);

//
// C-SPY user interface functions.
//

// C-SPY will display a message box window with the text given by the msg parameter.
// Text may be split on multiple lines by embedding newlines (\n) in the message string.
// The flash loader execution will halt until the message box OK button is pressed.
// The flash loader will then terminate and notify C-SPY that the flash download failed.
void cSpyFatalError(char* msg);

// C-SPY will display a message box window with the text given by the msg parameter.
// Text may be split on multiple lines by embedding newlines (\n) in the message string.
// The flash loader execution will halt until the message box OK button is pressed.
void cSpyMessageBox(char* msg);

// C-SPY will display a log message given by msg in the debug log window.
// Text may be split on multiple lines by embedding newlines (\n) in the message string.
void cSpyMessageLog(char* msg);

