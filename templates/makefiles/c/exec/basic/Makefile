CC = gcc

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)%.c=$(BUILD_DIR)%.o)

CFLAGS = -g -O2 -Wall -Wextra -pedantic -fsanitize=address
LDFLAGS = -g -Wall -Wextra -O2 -fsanitize=address
EXEC = $(BIN_DIR)/exec

.PHONY: all clean

all: $(EXEC)

%.o: %.c %.h
	gcc -o $@ -c $< $(CFLAGS)

$(EXEC): $(OBJECTS)
	gcc -o $@ $^ $(LDFLAGS)

clean:
	-rm *.o
	-rm $(EXEC)
