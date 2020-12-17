#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <byteswap.h>

#include "../include/des_types.h"
#include "../include/error.h"

void load_target(struct chunk *chunk, char *targetPath);
void load_key(key, char *keyPath);

#endif