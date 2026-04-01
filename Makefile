CC = gcc

SRC_DIR = src
LOG_DIR = logs
BUILD_DIR = build
BIN_DIR = bin

EXEC = $(BIN_DIR)/clide
LOGS = $(wildcard $(LOG_DIR)/*.txt)

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)%.c=$(BUILD_DIR)%.o)

CFLAGS = -g -Og -Wall -Wextra -pedantic -fsanitize=address
LDFLAGS = -g -Og -Wall -Wextra -pedantic -fsanitize=address 

.PHONY: all clean install

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(LDFLAGS)
	xxd -b $(EXEC) >> logs/cenv.txt

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c 
	$(CC) -c $< -o $@ $(CFLAGS)

test:
	./bin/clide init . -l c -f exec -d basic

install:
	cp -r templates ~/.local/share/maker

clean:
	-rm $(EXEC)
	-rm $(OBJECTS)
	-rm $(LOGS)

