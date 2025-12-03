CC = gcc
CFLAGS = -I src $(shell pkg-config --cflags sdl2)
LDFLAGS = $(shell pkg-config --libs sdl2)

SRCS = src/main.c src/engine/graphics/window.c src/engine/renderer/render_system.c src/engine/input/input.c
OBJS = $(SRCS:.c=.o)
TARGET = rpg_game

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
