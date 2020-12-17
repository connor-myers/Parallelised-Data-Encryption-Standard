/**
 * Handles all file input and ouput capabilities required for DES
 */

#include "../include/fileio.h"

/**
 * function: load_target
 * --------------------
 * Loads the bytes from the target file into a chunk
 * 
 * chunk:       Pointer to initialised chunk 
 * targetPath:  The filepath to the target file 
 */
void
load_target(struct chunk *chunk, char *targetPath)
{
        FILE *target = fopen(targetPath, "r");
        if (target == NULL)
                exit(INVALID_TARGET);

        uint8_t buffer[8] = {0};
        int bytesRead;
        while (bytesRead = fread(buffer, 1, 8, target), bytesRead > 0)
        {
                block block = 0;
                memcpy(&block, buffer, bytesRead);
                // bytes are wrong way around, otherwise
                block = __bswap_64(block);
                add_block(chunk, block);
        }   
}