CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g

TARGET = sqlite_clone
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
