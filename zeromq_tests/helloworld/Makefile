#SILENCE = @ 
CXX = gcc
CXX_FLAGS := -g -I/usr/include 
LD_FLAGS  := -L/usr/lib64 -lzmq  


SRCS     := $(wildcard *.c)
OBJS     := $(SRCS:.c=.o)
DEPS     := $(SRCS:.c=.d)


all: hwserver hwclient 

clean:
	        rm -f $(OBJS) $(DEPS)

$(OBJS): $(DEPS)

%.d: %.c
	        $(CXX) -M $(CXX_FLAGS) $< > $@

%.o: %.c
	        $(CXX) $(CXX_FLAGS) -c -o $@ $<

hwserver: hwserver.o
	        $(CXX) hwserver.o -o $@ $(LD_FLAGS)

hwclient: hwclient.o
	        $(CXX) hwclient.o -o $@ $(LD_FLAGS)
#ifneq ($(MAKECMDGOALS),clean)
#	-include $(DEPS)
