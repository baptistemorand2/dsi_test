////////////////////////////////////////////////////////////////
// Include 
////////////////////////////////////////////////////////////////

#include "socket_server_udp.h"

using namespace std;
////////////////////////////////////////////////////////////////
// Function
////////////////////////////////////////////////////////////////

Socket_server_udp::Socket_server_udp(const unsigned short int listenPort){
	listenSocket = socket(AF_INET, SOCK_DGRAM, 0);
	cout<<"socket create...";
	if (listenSocket <0) {//check if socket is well created
		cout << "NOK\n";
		exit(1);
	}
	cout<<"OK\n";
	
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(listenPort);
	cout<<"Bind...";
	if (bind(listenSocket,(struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
		cout << "NOK\n";
		exit(1);
	}
	cout<<"OK\n";
}

void Socket_server_udp::listenS(const unsigned int length){
	listen(listenSocket, length);
}

void Socket_server_udp::recv(struct sockaddr_in* clientAddress,char message[],const unsigned int length){
	socklen_t clientAddressLength=sizeof(*clientAddress);
	memset(message, 0x0, length);
	cout<<"try to receive a message....";
	if (recvfrom(listenSocket, message, length, 0,(struct sockaddr *) &(*clientAddress),&clientAddressLength) < 0) {
		cout<<"NOK\n";
	}
	cout<<"OK\n";
	// Affichage de l'adresse IP du client.
	cout << " from " << inet_ntoa(clientAddress->sin_addr);
	// Affichage du numéro de port du client.
	cout << ":" << ntohs(clientAddress->sin_port) << "\n";
	// Affichage de la ligne reçue
	cout << " Message : " << message << "\n";
	 
}
void Socket_server_udp::send(const struct sockaddr_in clientAddress,char message[],const unsigned int length){
	cout<<"try to send message...";
	if(sendto(listenSocket, message, length , 0, (struct sockaddr *) &clientAddress, sizeof(clientAddress)) < 0){
		cout<<"NOK\n";
	}
	else{
		cout<<"OK\n";
	}
	
}
Socket_server_udp::~Socket_server_udp(){
	cout<<"close socket\n";
	close(listenSocket);
}