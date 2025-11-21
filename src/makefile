CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = filesystem
SOURCES = main.c file_manager.c operations.c parser.c
HEADERS = file_manager.h operations.h parser.h

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: clean