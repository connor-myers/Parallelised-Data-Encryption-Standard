#include "../include/main.h"

int
main(int argc, char **argv)
{
        MPI_Init(&argc, &argv);

        // initialising MPI variables 
        int worldSize;
        int numWorkers;
        int myRank;
        MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
        MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
        numWorkers = worldSize - 1;

        if (myRank == 0) {
                // passing command-line arguments 
                struct user_settings settings;
                load_settings(&settings, argc - 1, argv + 1);
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
 * numArgs:     Number of command-line arguments (not including program name) 
 * args:        Command-line arguments (not including program name) 
 */
void
load_settings(struct user_settings *settings, int numArgs, char **args)
{
        // default values
        memset(settings, 0, sizeof(struct user_settings));
        
        // int c;
        // while((c = getopt(numArgs, args, "edk:")) != -1) {
        //         switch (c) {

        //         }
        // }                       
}