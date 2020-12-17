/**
 * Handles functions regarding the 64-bit key used in DES
 */

#include "../include/key.h"

void generate_random_key(key *key)
{
        // safe to put seed here - this is the only random generation we do
        srand(time(NULL));
        *key = 0;

        /*
        rand() cannot produce a 64 bit number on it's own
        So, we need to call it multiple times and shift the bits
        To generate a 64-bit number
        *key |=  rand() & 0xFF;
        */
        *key |= ((uint64_t)(rand() & 0xFF)) <<  8;
        *key |= ((uint64_t)(rand() & 0xFF)) << 16;
        *key |= ((uint64_t)(rand() & 0xFF)) << 24;
        *key |= ((uint64_t)(rand() & 0xFF)) << 32;
        *key |= ((uint64_t)(rand() & 0xFF)) << 40;
        *key |= ((uint64_t)(rand() & 0xFF)) << 48;
        *key |= ((uint64_t)(rand() & 0xFF)) << 56;
        *key |= ((uint64_t)(rand() & 0xFF)) << 64;
}

