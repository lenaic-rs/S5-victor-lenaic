CC=gcc
CFLAGS=-Wall -Werror

essai_pile: pile_io.o pile.o essai_pile.o
	$(CC) $^ -o $@ 

%.o: %.c 
	$(CC) $(CFLAGS) -c $<

pile.o: pile.h
pile_io.o: pile_io.h pile.h
essai_pile.o: pile_io.h pile.h

clean:
	rm -f *.o