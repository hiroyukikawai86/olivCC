CFLAGS=-Wall -std=c11
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

olivCC: $(OBJS)
	$(CC) -o olivCC $(OBJS) $(LDFLAGS)

test: olivCC
	./olivCC -test
	./test.sh

clean:
	rm -f olivCc *.o *~

