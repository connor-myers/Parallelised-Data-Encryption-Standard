#include "../include/des.h"

/* Permutation Table 1 */    
const uint8_t pc1[8][7] =       {
                                        {57, 49, 41, 33, 25, 17,  9},
                                        { 1, 58, 50, 42, 34, 26, 18},
                                        {10,  2, 59, 51, 43, 35, 27},
                                        {19, 11,  3, 60, 52, 44, 36},
                                        {63, 55, 47, 39, 31, 23, 15},
                                        { 7, 62, 54, 46, 38, 30, 22},
                                        {14,  6, 61, 53, 45, 37, 29},
                                        {21, 13,  5, 28, 20, 12,  4}
                                };

/* Permutation Table 2 */    
const uint8_t pc2[8][6] =       {
                                        {14, 17, 11, 24,  1,  5},
                                        { 3, 28, 15,  6, 21, 10},
                                        {23, 19, 12,  4, 26,  8},
                                        {16,  7, 27, 20, 13,  2},
                                        {41, 52, 31, 37, 47, 55},
                                        {30, 40, 51, 45, 33, 48},
                                        {44, 49, 39, 56, 34, 53},
                                        {46, 42, 50, 36, 29, 32}
                                };       

/* Initial Permutation Table (IP) */
const uint8_t ip[8][8] =        {
                                        {58, 50, 42, 34, 26, 18, 10,  2},
                                        {60, 52, 44, 36, 28, 20, 12,  4},
                                        {62, 54, 46, 38, 30, 22, 14,  6},
                                        {64, 56, 48, 40, 32, 24, 16,  8},
                                        {57, 49, 41, 33, 25, 17,  9,  1},
                                        {59, 51, 43, 35, 27, 19, 11,  3},
                                        {61, 53, 45, 37, 29, 21, 13,  5},
                                        {63, 55, 47, 39, 31, 23, 15,  7}
                                };

/* E-bit selection table */
const uint8_t eST[8][6] =      {
                                        {32,  1,  2,  3,  4,  5},
                                        { 4,  5,  6,  7,  8,  9},
                                        { 8,  9, 10, 11, 12, 13},
                                        {12, 13, 14, 15, 16, 17},
                                        {16, 17, 18, 19, 20, 21},
                                        {20, 21, 22, 23, 24, 25},
                                        {24, 25, 26, 27, 28, 29},
                                        {28, 29, 30, 31, 32,  1}
                                };        

/* The 8 Selection Tables */
const uint8_t sTables[8][4][16] =      {
                                                {
                                                        {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
                                                        { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
                                                        { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
                                                        {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}
                                                },

                                                {
                                                        {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
                                                        { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
                                                        { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
                                                        {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}
                                                },

                                                {
                                                        {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
                                                        {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
                                                        {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
                                                        { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}
                                                },

                                                {
                                                        { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
                                                        {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
                                                        {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
                                                        { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}
                                                },

                                                {
                                                        { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
                                                        {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
                                                        { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
                                                        {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}
                                                },

                                                {
                                                        {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
                                                        {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
                                                        { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
                                                        { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}
                                                },

                                                {
                                                        { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
                                                        {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
                                                        { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
                                                        { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12}
                                                },

                                                {
                                                        {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
                                                        { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
                                                        { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
                                                        { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}
                                                },
                                        };

 /* Permutation Table (for P function) */
const uint8_t p[8][4] =        {
                                        {16, 7,  20, 21},
                                        {29, 12, 28, 17},
                                        { 1, 15, 23, 26},
                                        { 5, 18, 31, 10},
                                        { 2,  8, 24, 14},
                                        {32, 27,  3,  9},
                                        {19, 13, 30,  6},
                                        {22, 11,  4, 25}
                                };  

/* Inverse Permutation Table */
const uint8_t ip_1[8][8] =     {
                                        {40,  8, 48, 16, 56, 24, 64, 32},
                                        {39,  7, 47, 15, 55, 23, 63, 31},
                                        {38,  6, 46, 14, 54, 22, 62, 30},
                                        {37,  5, 45, 13, 53, 21, 61, 29},
                                        {36,  4, 44, 12, 52, 20, 60, 28},
                                        {35,  3, 43, 11, 51, 19, 59, 27},
                                        {34,  2, 42, 10, 50, 18, 58, 26},
                                        {33,  1, 41,  9, 49, 17, 57, 25}
                                };

void
run_des(struct chunk *src, struct chunk *dst, key key, enum des_mode mode)
{
        // generate the 16 sub keys
        uint48 subKeys[NUM_SUB_KEYS];
        memset(subKeys, 0, sizeof(uint48) * NUM_SUB_KEYS);
        generate_subkeys(subKeys, key);

        printf("key=%016llx\n", key);
        for (int i = 0; i < 16; i++) {
                printf("%d: %llx\n", i, subKeys[i]);
        }

        
}

void
generate_subkeys(uint48 *subKeys, key key)
{
        // create K+
        uint56 kPlus = 0;
        create_k_plus(&kPlus, key);
        
        // create Cn, Dn for  0 >= n <= 16
        uint28 cBlocks[17];
        uint28 dBlocks[17];
        create_c_and_d_pairs(kPlus, cBlocks, dBlocks);

        // Now, we can actually create the subkeys
        uint56 cNdN;  // concatenation of Cn and Dn
        for (int k = 0; k < 16; k++) {
                cNdN = (((uint56) cBlocks[k + 1]) << 28) | dBlocks[k + 1];
                for (int i = 0; i < 8; i++) {
                        for (int j = 0; j < 6; j++) {
                                subKeys[k] |= (NTH_BIN_DIGIT(cNdN, 56 - pc2[i][j]))
                                                << (47 - (j + (6 * i)));
                        }
                }
        }   
}

void 
create_k_plus(uint56 *kPlus, key key)
{
        for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 7; j++) {
                        *kPlus |= (NTH_BIN_DIGIT(key, 64 - pc1[i][j])) << (55 - (j + (7 * i)));
                }
        }
}

void 
create_c_and_d_pairs(uint56 kPlus, uint28 *cBlocks, uint28 *dBlocks)
{
        /*
                cN (where  0 >= N <= 16) is first half of 56 bit kPlus (K+ in doc)
                dN is second half
                Each is a half of a 56 bit number, so they're both 28 bits
        */
        cBlocks[0] = (kPlus & 0x00FFFFFFF0000000) >> 28;
        dBlocks[0] =  kPlus & 0x000000000FFFFFFF;    

        /*
                Each cN or dN is formed by the previous value
                (i.e. Cn-1, Dn-1 respectively)
                By shifting that previous value according to a specific pattern
                of bits. We'll call this pattern a 'shiftMap'.
        */
        uint8_t shiftMap[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

        /*
                This 'shift' we do is not a normal left-bit shift.
                It is a *circular* bit-shift. So, when we shift one over,
                the previous MSB doesn't disappear, it becomes the LSB
                This why the shifting logic isn't just a simple
                'cBlocks[i] << shiftMap[i]';
        */
        for (int i = 0; i < 16; i++)
        {
                cBlocks[i + 1] = (((cBlocks[i] << shiftMap[i])
                                | (cBlocks[i] >> (28 - shiftMap[i]))) & 0x000000000FFFFFFF);
                dBlocks[i + 1] = (((dBlocks[i] << shiftMap[i])
                                | (dBlocks[i] >> (28 - shiftMap[i]))) & 0x000000000FFFFFFF);
        }
}


