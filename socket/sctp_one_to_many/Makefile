#SILENCE = @

C_FLAGS += -g 

all: server client

server: server.o main.o
	$(SILENCE)g++ $(C_FLAGS) -lsctp -o server server.o main.o
		
client: client.cpp  
	$(SILENCE)g++ $(C_FLAGS) -lsctp -o client client.cpp 

server.o: server.cpp server.h
	$(SILENCE)g++ $(C_FLAGS) -c server.cpp -o server.o
	
main.o: main.cpp
	$(SILENCE)g++ $(C_FLAGS) -c main.cpp -o main.o
	
clean:
	rm server client server.o main.o

