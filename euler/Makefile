#SILENCE = @

t = 26
d = f
n = 1100
m = 1000

ifneq ($(d),f)
    C_FLAGS += -g -D PRINT_LOG -D N=$(n) -D MAX_NUM=$(m) -lm
else
    C_FLAGS += -O3 -D N=$(n) -D MAX_NUM=$(m) -lm
endif

test.exe: test.o misc.o
	$(SILENCE)gcc $(C_FLAGS) -o test.exe test.o misc.o
		
misc.o: misc.c misc.h
	$(SILENCE)gcc $(C_FLAGS) -c misc.c
	
test.o: test$(t).c
	$(SILENCE)gcc $(C_FLAGS) -c test$(t).c -o test.o
	
clean:
	rm test.exe misc.o test.o

