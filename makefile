CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -Iinclude

TARGET = sqlite_clone
SRC = src/main.c src/types.c src/execute.c src/input.c src/meta.c src/row.c src/statement.c src/table.c
OBJ = build/main.o build/types.o build/execute.o build/input.o build/meta.o build/row.o build/statement.o build/table.o

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