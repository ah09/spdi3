TARGET = generate
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall

.PHONY: default all clean

default: $(TARGET)
generate: compare.h generateSPDI.o main.o minmax.o sort.o

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

compare.o: compare.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

generateSPDI.o: generateSPDI.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

minmax.o: minmax.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

sort.o: sort.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
