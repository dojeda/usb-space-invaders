CC=gcc
CFLAGS=-g -ggdb
OBJS=main.o renderer.o resources.o enemy.o game.o
LDFLAGS= -lglut -lGL -lGLU
TARGET= spaceinv

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)
#	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $(OBJS)

main.o: resources.h renderer.h game.h

renderer.o: renderer.h data.h resources.h game.h

resources.o: resources.h data.h game.h

enemy.o: data.h 

game.o: game.h resources.h data.h 

.PHONY: clean

clean:
	rm $(TARGET) $(OBJS)
