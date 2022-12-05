BIN:=address_book
SRCS:=$(wildcard *.c)
OBJS:=$(SRCS:.c=.o)

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $@ $^

clean:
	$(RM) $(BIN) $(OBJS)