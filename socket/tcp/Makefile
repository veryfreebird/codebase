#SILENCE = @

C_FLAGS += -g 

all: server client

server: server.c
	$(SILENCE)g++ $(C_FLAGS) -o server server.cpp 
		
client: client.c  
	$(SILENCE)g++ $(C_FLAGS) -o client client.cpp 

clean:
	rm server client 

