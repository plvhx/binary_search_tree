CC = gcc
CFLAGS = -O3 -std=c99 -fPIC -Wall -Werror
LIB_OBJS = ./bs_tree.o	
LIBRARY = ./bs_tree.so

$(LIBRARY): $(LIB_OBJS)
	$(CC) -shared -Wl,--export-dynamic $(LIB_OBJS) -o $(LIBRARY)

tests:
	$(CC) -o bs_tests bs_tests.c ./bs_tree.so

clean:
	rm -f *.o *.so ./bs_tests
