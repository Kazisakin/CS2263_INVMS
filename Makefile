all:
	gcc -Wall -Wextra -std=c11 -c item.c
	gcc -Wall -Wextra -std=c11 -c inventory.c
	gcc -Wall -Wextra -std=c11 -c main.c
	gcc -Wall -Wextra -std=c11 -o inventory item.o inventory.o main.o

clean:
	rm -f *.o inventory test_inventory test_inventory.txt

test:
	gcc -Wall -Wextra -std=c11 -c item.c
	gcc -Wall -Wextra -std=c11 -c inventory.c
	gcc -Wall -Wextra -std=c11 -c test.c
	gcc -Wall -Wextra -std=c11 -o test_inventory item.o inventory.o test.o
	./test_inventory