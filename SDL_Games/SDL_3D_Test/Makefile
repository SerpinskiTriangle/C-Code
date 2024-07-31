CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I../include -Iheaders/
LDFLAGS = -lSDL2 -L../lib -lm 

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)
EXEC = 3D_Test

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJS)
