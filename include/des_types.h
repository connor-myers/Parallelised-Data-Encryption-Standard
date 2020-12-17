#ifndef DES_TYPES_H
#define DES_TYPES_H

/**
 * Contains custom data structures that are useful in the context of
 * DES Encryption 
 */

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#define MIN_CHUNK_SIZE 1024
#define CHUNK_GROWTH_RATE 2

typedef uint64_t block; // a 'block' in DES is 64-bits
typedef uint64_t key;   // keys in DES are 64-bits

// these typdefs make des algorithm more readable
typedef uint64_t uint56;
typedef uint64_t uint48;
typedef uint32_t uint28;

/**
 * enum: des_mode
 * ----------------------
 * Different possible modes for des - encryption or decryption
 */
enum des_mode {
        INVALID,
        ENCRYPTION,
        DECRYPTION
};

/**
 * struct: chunk
 * -------------
 * A chunk is a collection of blocks. 
 * Chunks are implemented as a heap-allocated Array List 
 * 
 * blocks:      Expandable array of blocks
 * size:        The total number of blocks in the chunk
 * capacity:    The number of blocks that can fit in blocks.
 *              Capacity grows by a factor of 2 each
 *              time capacity is reached
 */
struct chunk
{
        block *blocks;    
        size_t size;
        size_t capacity;    
};

void init_chunk(struct chunk *chunk);
void add_block(struct chunk *chunk, block block);
void free_chunk(struct chunk *chunk);

#endif