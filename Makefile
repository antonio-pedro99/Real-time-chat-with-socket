all:
	gcc -o a.out node_1.c
	gcc -o b.out node_2.c
clean:
	rm -f  sockN1 sockN2
