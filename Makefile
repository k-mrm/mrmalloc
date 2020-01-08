mrmalloc: ./src/main.o ./src/malloc.o
	gcc -o mrmalloc ./src/main.o ./src/malloc.o
main.o: ./src/main.c
	gcc -c ./src/main.c
malloc.o: malloc.c
	gcc -c ./src/malloc.c

clean:
	rm -f ./src/*.o
