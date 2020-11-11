OUTPUT=interpret
OBJECTS=interpret.o instruction.o io.o
CFLAGS=-g -Wall -fsanitize=address -std=c99
LFLAGS=-lm

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

%.o: %.c
	gcc $(CFLAGS) -c $<

all: $(OUTPUT)

interpret: $(OBJECTS)
	gcc $(CFLAGS) -g -o $@ $^ $(LFLAGS)

clean:
	rm -f *.o $(OUTPUT)
