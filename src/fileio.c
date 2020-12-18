/**
 * Handles all file input and ouput capabilities required for DES
 */

#include "../include/fileio.h"

/**
 * function: load_target
 * ---------------------
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

        fclose(target);
}

/**
 * function: save_chunk
 * ---------------------
 * Saves the bytes of the chunk to a file called filePath
 * 
 * chunk:       The chunk to be saved
 * targetPath:  The filepath to save the file as 
 */
void
save_chunk(struct chunk *chunk, char *filePath)
{
        FILE *file = fopen(filePath, "wb");
        if (file == NULL) {
                exit(INVALID_SAVE);
        }

        for (int i = 0; i < chunk->size; i++) {
                chunk->blocks[i] = __bswap_64(chunk->blocks[i]);
        }
        fwrite(chunk->blocks, sizeof(block), chunk->size, file);

        fclose(file);
}

/**
 * function: load_key
 * ------------------
 * Loads the 64-bit key from key file
 * 
 * key:         Pointer to a key; does not need to be zero       
 * keyPath:     The file path to the key file
 */
void
load_key(key *key, char *keyPath)
{
        *key = 0; // ensure it's 0 so no bit-magic weirdness occurs
        FILE *keyFile = fopen(keyPath, "rb");
        if (keyFile == NULL)
                exit(INVALID_KEY);

        int bytesRead = fread(key, sizeof(*key), 1, keyFile);
        *key = __bswap_64(*key); 

        fclose(keyFile);
}

/**
 * function: save_key
 * ------------------
 * Saves a 64-bit key to a file
 * 
 * key:         The key to be saved to a file       
 * keyPath:     The path of the key-file to be created
 */
void
save_key(key key, char *keyPath)
{
        key = __bswap_64(key);
        FILE *keyFile = fopen(keyPath, "wb"); 
        if (keyFile == NULL)
                exit(INVALID_KEY);
        int bytesWritten = fwrite(&key, 8, 1, keyFile);
        if (bytesWritten == 0)
                exit(INVALID_KEY);

        fclose(keyFile);
}