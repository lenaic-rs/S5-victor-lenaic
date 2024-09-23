
CFLAGS= -Wall -Werror
CC=gcc

all: mesure_tris

mesure_tris: mesure_tris.o tris.o
	$(CC) $(CFLAGS) mesure_tris.o tris.o -o mesure_tris

clean:
	rm -f mesure_tris *.o

plot:
	gnuplot ./plot.txt -p

plot-seg:
	gnuplot ./plot_segmentation.txt -p