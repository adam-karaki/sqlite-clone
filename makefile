CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -Iinclude

TARGET = sqlite_clone
SRC = src/main.c src/types.c src/compiler.c
OBJ = build/main.o build/types.o build/compiler.o

all: $(TARGET)

build:
	mkdir -p build

$(TARGET): build $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

run: $(TARGET)
	./$(TARGET)

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)