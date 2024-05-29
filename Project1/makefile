CC = gcc
BIN_DIR = .\build
SRC_DIR = .\src
SOURCES = $(SRC_DIR)\main.c
TARGET = $(BIN_DIR)\main.o
CFLAGS = -g -Wall

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: run clean

run: $(TARGET)
	$(TARGET)

clean:
	@del /q $(TARGET)

