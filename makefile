proj4: proj4a.o proj4b.o proj4c.o
	gcc -o a.out proj4a.o proj4b.o proj4c.o

proj4a.o: proj4a.c proj4.h
	gcc -c proj4a.c

proj4b.o: proj4b.c proj4.h
	gcc -c proj4b.c

proj4c.o: proj4c.c proj4.h
	gcc -c proj4c.c

clean:
	rm proj4a.o proj4b.o proj4c.o proj4
