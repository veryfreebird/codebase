#SILENCE = @
C_FLAGS += -g 

iptest: ghash_bucket.o iptest.o jhash.o 
	$(SILENCE)gcc $(C_FLAGS) -o iptest ghash_bucket.o iptest.o jhash.o 
		
iptest.o: iptest.c dlist.h ghash_bucket.h jhash.h 
	$(SILENCE)gcc $(C_FLAGS) -c iptest.c
	
ghash_bucket.o: ghash_bucket.c ghash_bucket.h jhash.h dlist.h
	$(SILENCE)gcc $(C_FLAGS) -c ghash_bucket.c -o ghash_bucket.o
	
jhash.o: jhash.c jhash.h
	$(SILENCE)gcc $(C_FLAGS) -c jhash.c -o jhash.o

clean:
	rm iptest *.o 

