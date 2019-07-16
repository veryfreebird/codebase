TARGET = md5c
CC = gcc
src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = 

$(TARGET): $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) $(TARGET)

print-% : ; @echo $* = $($*)


#source: http://nuclear.mutantstargoat.com/articles/make/
