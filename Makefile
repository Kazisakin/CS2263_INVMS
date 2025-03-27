CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

TARGET = filesystem_sim

all: $(TARGET)

$(TARGET): main.o filesystem.o
	$(CC) $(CFLAGS) main.o filesystem.o -o $(TARGET)

main.o: main.c filesystem.h
	$(CC) $(CFLAGS) -c main.c

filesystem.o: filesystem.c filesystem.h
	$(CC) $(CFLAGS) -c filesystem.c

clean:
	rm -f *.o $(TARGET)
