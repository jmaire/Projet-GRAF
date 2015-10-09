CC=gcc
CFLAGS=
SRC=*.c
OBJ=$(SRC: .c=.o)
EXEC=TP2

$(EXEC): $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)

%.o: %.c %.h
	$(CC) -o $@ $(CFLAGS) $<

CLEAN:
	rm *.o, rm $(EXEC)
