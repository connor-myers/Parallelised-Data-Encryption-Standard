#ifndef DES_H
#define DES_H

#include "mpi.h"

#include "../include/des_types.h"

#define NUM_SUB_KEYS 16

#define NTH_BIN_DIGIT(X, N) (X >> N) & 1

/* grabbing global mpi variables from main.c */
extern int myRank;
extern int worldSize;
extern int numWorkers;

void run_des(struct chunk *src, struct chunk *dst, key key, enum des_mode mode);
void worker_des();
void generate_subkeys(uint48 *subKeys, key key);
void create_k_plus(uint56 *kPlus, key key);
void create_c_and_d_pairs(uint56 kPlus, uint28 *cBlocks, uint28 *dBlocks);
void des_on_block(int mode, uint48 *subKeys, block *src, block *dst);
void encode_block(block *encoded, block block);
u_int32_t f(u_int32_t rN_1, u_int64_t kN);
uint48 E(u_int32_t rN_1);
u_int8_t S(uint6 Bi, uint8_t boxNum);
u_int32_t P(u_int32_t sCompiled);
block inverse_permutation(block block);

#endif 