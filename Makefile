CC	=	mpicc
CFLAGS	=	-Wall -pedantic -O3 -g -w -std=gnu99 -fopenmp

SRC := src
OBJ := obj
BIN := bin

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

$(BIN)/des: $(OBJECTS)
	$(CC) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -I$(SRC) -c $< -o $@

clean:
	rm -rf obj/* bin/* completed des_key.key
