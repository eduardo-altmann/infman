CC = gcc
CFLAGS = -Wall -Iinclude -O2
LDFLAGS = -lraylib -lm

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
TARGET = build/main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(TARGET)

.PHONY: all clean
