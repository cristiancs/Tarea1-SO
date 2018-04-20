TARGET = prog
CC = gcc
CFLAGS = -Wall

.PHONY: default all clean

default: $(TARGET)

all: default

OBJECTS = src/fileManager.c src/acciones.c src/app.c
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $@

run:
	./$(TARGET)

cf:
	-rm -rf data
clean:
	-rm -rf data
	-rm -f *.o
	-rm -f $(TARGET)