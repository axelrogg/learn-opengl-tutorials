CC = gcc
CFLAGS = -Iinclude
LIBS = -lGL -lglfw3 -lX11 -lpthread -lXrandr -lXi -ldl -lm

SRCDIR = src
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/glad.c
OUTPUT = snake

all: $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SOURCES) $(LIBS)

clean:
	rm -f $(OUTPUT)
