/**
 * Defines the error codes for the program  
 */

/**
 * enum: error_codes
 * ----------------------
 * All possible error codes for program
 */
enum error_codes 
{
        NORMAL,         // program exited normally
        INVALID_ARGS,   // program exited due to invalid command-line args
        INVALID_TARGET, // program exited due to an invalid target file
        INVALID_KEY     // program exited due to bad key file
};