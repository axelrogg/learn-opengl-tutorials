CC = gcc
CFLAGS = -Iext -Iinclude
LIBS = -lGL -lglfw3 -lX11 -lpthread -lXrandr -lXi -ldl -lm

SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)
OUTPUT = snake

all: $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SOURCES) $(LIBS)

clean:
	rm -f $(OUTPUT)
