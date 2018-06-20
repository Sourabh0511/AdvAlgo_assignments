output: client.o functions.o
	gcc client.o functions.o -o output -lm

client.o: client.c
	gcc -c client.c

functions.o: functions.c
	gcc -c functions.c -lm

clean:
	rm -rf *.o

run:
	./output < input.txt 
