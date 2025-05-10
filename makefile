CC = gcc
CFLAGS = -Wall -pthread
TARGET = webserver

OBJS = main.o server.o parse.o web_routes.o error.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c server.h
	$(CC) $(CFLAGS) -c main.c

server.o: server.c server.h parse.h
	$(CC) $(CFLAGS) -c server.c

parse.o: parse.c parse.h web_routes.h error.h
	$(CC) $(CFLAGS) -c parse.c

web_routes.o: web_routes.c web_routes.h error.h
	$(CC) $(CFLAGS) -c web_routes.c

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c

clean:
	rm -f *.o $(TARGET)