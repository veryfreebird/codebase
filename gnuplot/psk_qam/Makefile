#SILENCE = @

C_FLAGS += -g -Wall

all: qpsk qam mpsk

qpsk: qpsk.c 
	$(SILENCE)gcc $(C_FLAGS) -o qpsk -lm qpsk.c
		
qam: qam.c  
	$(SILENCE)gcc $(C_FLAGS) -o qam -lm qam.c 

mpsk: mpsk.c  
	$(SILENCE)gcc $(C_FLAGS) -o mpsk -lm mpsk.c 

clean:
	rm qpsk qam mpsk 
