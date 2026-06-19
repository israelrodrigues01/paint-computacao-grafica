CC = gcc

SRC = src/main.c \
      src/render.c \
      src/input.c \
      src/paint.c \
      src/file.c

LIBS = -lGL -lGLU -lglut

all:
	$(CC) $(SRC) -o app $(LIBS)
	./app

run:
	./app