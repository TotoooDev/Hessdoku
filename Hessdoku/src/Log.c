#include <Log.h>
#include <stdarg.h>

void logImplementation(const char* message, ...)
{
    // Open the log file
    FILE* logFile = fopen("sudoku.log", "a");
    ASSERT(logFile != NULL, "Failed to open log file!");

    // Start the variadic arguments thing
    // https://www.geeksforgeeks.org/variadic-functions-in-c/
    va_list parameters;
    va_start(parameters, message);

    // Print the message
    vfprintf(logFile, message, parameters);

    // Close stuff
    va_end(parameters);
    fclose(logFile);
}
