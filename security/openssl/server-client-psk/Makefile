#SILENCE = @

C_FLAGS += -g -Wall

all: server client

server: server.c 
	$(SILENCE)gcc $(C_FLAGS) -o server -lssl -lcrypto server.c
		
client: client.c  
	$(SILENCE)gcc $(C_FLAGS) -o client -lssl -lcrypto client.c 

clean:
	rm server client 
