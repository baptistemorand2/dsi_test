CC=g++
CFLAGS=-W -Wall -ansi -pedantic -g
LDFLAGS=-pthread -g
EXEC=mainS mainC

all: $(EXEC)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

mainS: socket_server_udp.o socket_server_tcp.o mainS.o
	$(CC) -o $@ $^ $(LDFLAGS)
	
mainC: socket_client_udp.o  socket_client_tcp.o mainC.o



clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)