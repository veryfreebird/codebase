#SILENCE = @

C_FLAGS += -g 

all: server client

server: server.c
	$(SILENCE)gcc $(C_FLAGS) -o server server.c 
		
client: client.c  
	$(SILENCE)gcc $(C_FLAGS) -o client client.c 

clean:
	rm server client 

