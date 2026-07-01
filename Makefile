UNAME_S := $(shell uname -s)
 
SRC = src/main.c \
			src/render.c \
			src/input.c \
			src/paint.c \
			src/selection.c \
			src/file.c \
			src/transformacoes.c \
			src/earclipping.c
 
 
ifeq ($(UNAME_S),Darwin)
CC = clang
LIBS = -DGL_SILENCE_DEPRECATION -framework OpenGL -framework GLUT -lm
else
CC = gcc
LIBS = -lGL -lGLU -lglut -lm
endif
 
all:
	$(CC) $(SRC) -o app $(LIBS)
	./app
 
run:
	./app
 
build:
	$(CC) $(SRC) -o app $(LIBS)
 