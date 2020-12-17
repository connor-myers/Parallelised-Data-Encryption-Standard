/**
 * Manages the custom data structures for DES
 */

#include "../include/des_types.h"

/**
 * function: init_chunk
 * --------------------
 * Initialises a new chunk
 * 
 * chunk: Pointer to empty chunk struct to be initialised
 */
void
init_chunk(struct chunk *chunk)
{
        chunk->size = 0;
        chunk->capacity = MIN_CHUNK_SIZE;
        chunk->blocks = (block*) malloc(sizeof(block) * chunk->capacity);
}

/**
 * function: init_chunk
 * --------------------
 * Adds a new block to the specified chunk
 * 
 * chunk: The chunk to add the block to
 * block: The block to be added
 */
void
add_block(struct chunk *chunk, block block)
{
        // If we don't have room for block, make more
        if (chunk->size >= chunk->capacity) {
                chunk->capacity *= CHUNK_GROWTH_RATE;
                chunk->blocks = realloc(chunk->blocks,
                        chunk->capacity * sizeof(block));
        }

        // guaranteed to have space for new block now. Add it risk free.
        chunk->blocks[chunk->size] = block;
        chunk->size++;
}

/**
 * function: free_data
 * --------------------
 * Releases heap allocated memory for a chunk and resets
 * all values
 * 
 * chunk: the chunk to have its memory reclaimed
 */
void
free_data(struct chunk *chunk)
{
        free(chunk->blocks);
        memset(chunk, 0, sizeof(struct chunk));
}