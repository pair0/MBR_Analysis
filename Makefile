all: mbr

mbr: mbr.o
	g++ -o mbr mbr.o

mbr.o: mbr.c
	g++ -c -o mbr.o mbr.c

clean:
	rm -f mbr
	rm -f *.o