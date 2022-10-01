all: testQueue testLL

testQueue: linkedListQueue.h linkedListQueue.c testQueue.c
	gcc -g -Wall -std=c99 -o testQueue linkedListQueue.c testQueue.c

testLL: linkedList.h linkedList.c testLL.c
	gcc -g -Wall -std=c99 -o testLL linkedList.c testLL.c

clean:
	rm testADT testLL
