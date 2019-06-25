#SILENCE = @

C_FLAGS += -g 

all: unshare_test uts_ns

unshare_test: unshare_test.c 
	$(SILENCE)gcc $(C_FLAGS) -o unshare_test unshare_test.c
		
uts_ns: uts_ns.c  
	$(SILENCE)gcc $(C_FLAGS) -o uts_ns uts_ns.c 

clean:
	rm unshare_test uts_ns 

