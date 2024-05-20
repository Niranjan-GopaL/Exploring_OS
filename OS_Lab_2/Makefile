CC = gcc

# All C files in ./ is in SOURCES
SOURCES := $(wildcard *.c)

# Generating executable names with SAME NAME as it's C file in SOURCES 
EXECUTABLES := $(SOURCES:.c=)

all: $(EXECUTABLES)

%.out: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXECUTABLES)
	rm -f fifo*
