out: client.o bfunc.o
	gcc client.o bfunc.o -o out -lm

client.o: client.c
	gcc -c -std=c99 client.c

bfunc.o: bfunc.c
	gcc -c -std=c99 bfunc.c

clean:
	rm -rf *.o

exe:
	./out < conv_csv_dataset.txt
