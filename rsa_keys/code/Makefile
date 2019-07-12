CC  = gcc
CPP = g++
RM  = rm -rf

## debug flag
DBG_ENABLE   = 0

## source file path
SRC_PATH  := .

## target exec file name
TARGET    := rsatest

## get all source files
SRCS      += $(wildcard $(SRC_PATH)/*.cpp)

## all .o based on all .c
OBJS      := $(SRCS:.cpp=.o)


## need libs, add at here
LIBS :=

## used headers  file path
INCLUDE_PATH := ./

## used include librarys file path
LIBRARY_PATH := /lib

## debug for debug info, when use gdb to debug
ifeq (1, ${DBG_ENABLE}) 
    CFLAGS += -D_DEBUG -O0 -g -DDEBUG=1
endif

## get all include path
CFLAGS  += $(foreach dir, $(INCLUDE_PATH), -I$(dir))

## get all library path
LDFLAGS += $(foreach lib, $(LIBRARY_PATH), -L$(lib))

## get all librarys
LDFLAGS += $(foreach lib, $(LIBS), -l$(lib))

build: $(OBJS)
	$(CPP) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

#可自动推导.o文件生成规则 
include $(SRCS:.cpp=.d)

%d: %cpp
	@echo "create depend"
	$(CPP) -MM $(CFLAGS) $< > $@.
	; \
 	sed 's,$∗$∗\.o[ :]*,\1.o $@ ,g' < $@.
	> $@; \
	$(RM) $@.

clean:
	$(RM) $(OBJS) $(TARGET)

include $(SOURCES:.c=.d)
%d: %c
	@echo "create depend"
	$(CC) -MM $(CFLAGS) $< > $@.
	; \
    sed 's,$∗$∗\.o[ :]*,\1.o $@ ,g' < $@.
	> $@; \
	$(RM) $@.