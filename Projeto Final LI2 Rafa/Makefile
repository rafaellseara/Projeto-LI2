CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O2
LDFLAGS = -lncurses -lm
TARGET = jogo

SRCS = Main.c Menu.c Mobs.c Map.c Game.c Guns.c Player.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

