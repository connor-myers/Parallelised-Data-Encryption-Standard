# Parallelised-Data-Encryption-Standard
A parallelised implementation of the Data Encryption Standard (DES) using C and MPI

## Introduction

The purpose of this project is to produce a high-performant software-based implementation of the Data Encryption
Standard (DES). The project was implemented in C, using the OpenMPI library for parallelisation.
Paralleisation of the initial serial implementation increased performance by approximately 8 times.

## DES Algorithm

The Data Encryption Standard (DES) is a block-based, symmetric encryption algorithm invented by IMB in
the 1970s. DES is considered ’symmetric’ as it uses identical keys for both encryption and decryption (as opposed
to asymmetric cryptographic algorithms which utilise a public and private key, such as RSA). Furthermore, DES
is a block-based algorithm as it encrypts blocks of 8 bytes at a time, a property which was heavily exploited in the
parallel implementation.
DES uses a 56-bit key; this makes it particularly vulernable to brute-force attacks from modern hardware. DES
is not secure and has been so for a number of years. The algorithm was broken with a brute-force attack in 1999
in just over 22 hours.
Despite DES being completely redundant in face of modern-computing power, the DES algorithm lives on in the
form of 3DES. 3DES, i.e. Triple DES, was invented in 1995 in wake of the growing concern that DES would soon be
broken. Evidently, this was a good choice as, just four years later, DES was cracked for the very first time. 3DES
utilises the same algorithm as DES; it simply applies the DES algorithm three times (hence the name) utilising
three unique keys. This gives it an effective key-size of 168 bits. 3DES, to this day, is still considered secure.
(Sort of, but not really since AES is both more secure and faster than 3DES so there really isn't any point in using any variation of the DES algorithm in this day and age)
So, while DES is slow and horrible (by design; compared to modern algorithms such as AES) this was still a fun and rewarding project.

## Requirements
- POSIX complient OS
- OpenMPI

## How To Run

### Example:
```bash
mpiexec -n 12 bin/des -e tst/test.txt
```
This will generate a .key file and a completed file.
The .key file contains the key and the completed file contains the cipher text.
In order to decrypt this file, you would run:
```bash
mpiexec -n 12 bin/des -d -k des_key.key completed
```
This will overwrite the completed file with the decrypted plain-text.

Note: the '12' specified on the -n flag is merely an example and should, for optimum results, be set to the number of cores on your CPU.
