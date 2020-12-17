#include "../include/main.h"

// keep global so we can access from des.c
int worldSize;
int numWorkers;
int myRank;

int
main(int argc, char **argv)
{
        MPI_Init(&argc, &argv);

        // initialising MPI variables 
        MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
        MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
        numWorkers = worldSize - 1;

        if (myRank == 0) {
                // passing command-line arguments 
                struct user_settings settings;
                load_settings(&settings, argc, argv);

                // load target into chunk
                struct chunk target;
                init_chunk(&target);
                load_target(&target, settings.target);

                // setup-key
                key key = 0;
                if (settings.key != NULL) {
                        load_key(&key, settings.key);
                } else {
                        generate_random_key(&key);
                        save_key(key, "des_key.key");
                }

                // initialise destination chunk
                struct chunk destination;
                init_chunk(&destination);

                // apply DES
                run_des(&target, &destination, key, settings.mode);
        }

        MPI_Finalize(); 

        return 0;
}

/**
/**
 * function: user_settings
 * -----------------------
 * Loads command-line arguments into user settings struct
 * 
 * settings:    pointer to empty user_settings struct. Will get filled with
 *              corresponding arguments from commandline arguments
 * numArgs:     Number of command-line arguments 
 * args:        Command-line arguments
 */
void
load_settings(struct user_settings *settings, int numArgs, char **args)
{
        // default values
        memset(settings, 0, sizeof(struct user_settings));
        
        int c;
        while((c = getopt(numArgs, args, "edk:")) != -1) {
                switch (c) {
                        case 'e':
                                settings->mode = ENCRYPTION;
                                break;
                        case 'd':
                                settings->mode = DECRYPTION;
                                break;
                        case 'k':
                                settings->key = optarg;
                                break;
                }
        }

        // grabbing target file, which should be last arg
        if (optind != numArgs - 1) {
                usage();
        } else {
                settings->target = args[optind];
        }

        // checking all settings are valid
        if (settings->mode == INVALID || settings->target == NULL) {
                usage();
        }   
}

void
usage()
{
        fprintf(stderr, "usage: -ed [-k key] target\n");
        exit(INVALID_ARGS);        
}