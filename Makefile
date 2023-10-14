CC = gcc
CFLAGS = -Iext -Iinclude
LIBS = -lGL -lglfw3 -lX11 -lpthread -lXrandr -lXi -ldl -lm

SRCDIR = src
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/glad.c $(SRCDIR)/utils.c $(SRCDIR)/shaders.c $(SRCDIR)/stb_image.c
OUTPUT = snake

all: $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SOURCES) $(LIBS)

clean:
	rm -f $(OUTPUT)
