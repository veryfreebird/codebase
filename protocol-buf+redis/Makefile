#SILENCE = @ 
SERVER = 127.0.0.1
CXX = g++
CXX_FLAGS := -g $(shell pkg-config --cflags protobuf) $(shell pkg-config --cflags hiredis) 
LD_FLAGS  := $(shell pkg-config --libs protobuf)  $(shell pkg-config --libs hiredis)  

PROTOS         := $(wildcard *.proto)
PROTO_OBJS     := $(PROTOS:.proto=.pb.o)

BINS     := mytest

SRCS     := $(wildcard *.cpp)
OBJS     := $(SRCS:.cpp=.o)
DEPS     := $(SRCS:.cpp=.d)

PBSRCS   := $(wildcard *.proto)
PBOBJS   := $(PROTOS:.proto=.pb.o)
PBGENS   := $(PROTOS:.proto=.pb.cc) $(PROTOS:.proto=.pb.h)

all: $(BINS)

clean:
	        rm -f $(BINS) $(OBJS) $(DEPS) $(PBOBJS) $(PBGENS)

$(BINS): $(OBJS)
$(OBJS): $(DEPS)
$(DEPS): $(PBOBJS)

.PRECIOUS: $(PBGENS)

%.d: %.cpp
	        $(CXX) -M $(CXX_FLAGS) $< > $@

%.pb.cc: %.proto
	        protoc --cpp_out=. $<

%.pb.o : %.pb.cc
	        $(CXX) $(CXX_FLAGS) -c -o $@ $<

%.o: %.cpp
	        $(CXX) $(CXX_FLAGS) -c -o $@ $<

$(BINS): %: %.o
	        $(CXX) -o $@ $(PROTO_OBJS) $^ $(LD_FLAGS)

#ifneq ($(MAKECMDGOALS),clean)
#	-include $(DEPS)
#endif

run:
	taskset 0x01 ./mytest $(SERVER)
