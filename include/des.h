#ifndef DES_H
#define DES_H

#include "../include/des_types.h"

#define NUM_SUB_KEYS 16

#define NTH_BIN_DIGIT(X, N) (X >> N) & 1

/* grabbing global mpi variables from main.c */
extern int myRank;
extern int worldSize;
extern int numWorkers;

void run_des(struct chunk *src, struct chunk *dst, key key, enum des_mode mode);
void generate_subkeys(uint48 *subKeys, key key);
void create_k_plus(uint56 *kPlus, key key);
void create_c_and_d_pairs(uint56 kPlus, uint28 *cBlocks, uint28 *dBlocks);

#endif 