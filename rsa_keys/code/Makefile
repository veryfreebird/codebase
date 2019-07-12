CC = g++
src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

LDFLAGS = 

rsatest: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) rsatest

print-% : ; @echo $* = $($*)