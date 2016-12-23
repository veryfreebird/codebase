#SILENCE = @
#C_FLAGS += -g

test: test.o foo.o
	$(SILENCE)gcc $(C_FLAGS) -o test test.o foo.o
		
foo.o: foo.c
	$(SILENCE)gcc $(C_FLAGS) -c foo.c
	
test.o: test.c
	$(SILENCE)gcc $(C_FLAGS) -c test.c -o test.o
	
clean:
	rm test foo.o test.o

