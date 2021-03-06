#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <getopt.h>

#include "mpi.h"
#include "../include/des.h"
#include "../include/des_types.h"
#include "../include/fileio.h"
#include "../include/key.h"

/**
 * struct: user_settings
 * ----------------------
 * Contains parsed user-settings from command-line arguments
 * mode:        Represents whether user is encrypting (1) or decryption (2).
 * key:         The path to the .key file containing key. NULL if not specified.
 * target:      The path to the file to be encrypted or decrypted
 */
struct user_settings
{
        enum des_mode   mode;
        char            *key;
        char            *target;
};

/**
 * function: user_settings
 * -----------------------
 * Loads command-line arguments into user settings struct
 */
void load_settings(struct user_settings *settings, int numArgs, char **args);

/**
 * function: user_settings
 * -----------------------
 * Prints usage message to stderr
 */
void usage();

#endif