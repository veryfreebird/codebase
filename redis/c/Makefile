#SILENCE = @ 
SERVER = 127.0.0.1
CXX = gcc
CXX_FLAGS := -g $(shell pkg-config --cflags hiredis) 
LD_FLAGS  := $(shell pkg-config --libs hiredis)  


BINS     := mytest

SRCS     := $(wildcard *.c)
OBJS     := $(SRCS:.c=.o)
DEPS     := $(SRCS:.c=.d)


all: $(BINS)

clean:
	        rm -f $(BINS) $(OBJS) $(DEPS) 

$(BINS): $(OBJS)
$(OBJS): $(DEPS)


%.d: %.c
	        $(CXX) -M $(CXX_FLAGS) $< > $@

%.o: %.c
	        $(CXX) $(CXX_FLAGS) -c -o $@ $<

$(BINS): 
	        $(CXX) -o $@ $^ $(LD_FLAGS)

#ifneq ($(MAKECMDGOALS),clean)
#	-include $(DEPS)
#endif
