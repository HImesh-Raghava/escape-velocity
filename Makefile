CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lncurses -lm

SRC = main.c render.c physics.c sb.c
OBJ = main.o render.o physics.o sb.o
EXEC = escape_v

all: $(EXEC)

$(EXEC): $(OBJ)
    $(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c game.h
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJ) $(EXEC)
