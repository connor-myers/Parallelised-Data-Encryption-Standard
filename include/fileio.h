#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <byteswap.h>

#include "../include/des_types.h"
#include "../include/error.h"

void load_target(struct chunk *chunk, char *targetPath);
void save_chunk(struct chunk *chunk, char *filePath);
void load_key(key *key, char *keyPath);
void save_key(key key, char *keyPath);

#endif