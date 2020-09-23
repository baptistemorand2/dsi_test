////////////////////////////////////////////////////////////////
// Include 
////////////////////////////////////////////////////////////////

#include "socket_server_tcp.h"

using namespace std;
////////////////////////////////////////////////////////////////
// Function
////////////////////////////////////////////////////////////////

Socket_server_tcp::Socket_server_tcp(const unsigned short int listenPort){
	listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	cout<<"socket create...";
	if (listenSocket <0) {//check if socket is well created
		cout << "NOK\n";
		exit(1);
	}
	cout<<"OK\n";
	
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);//Server no filter on addr
	serverAddress.sin_port = htons(listenPort);
	cout<<"Bind...";
	if (bind(listenSocket,(struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
		cout << "NOK\n";
		exit(1);
	}
	cout<<"OK\n";
}

void Socket_server_tcp::listenS(const unsigned int length){
	listen(listenSocket, length);
}

void Socket_server_tcp::recvM(int socketId,char message[],const unsigned int length){
	memset(message, 0x0, length);
	cout<<"try to receive a message....";
	if (recv(socketId, message, length, 0) < 0) {
		cout<<"NOK\n";
	}
	cout<<"OK\n";
	// Affichage de l'adresse IP du client.
	cout << " from socketId : " <<socketId ;
	// Affichage de la ligne reçue
	cout << " Message : " << message << "\n";
	 
}
void Socket_server_tcp::sendM(int socketId,char message[],const unsigned int length){
	cout<<"try to send message("<<socketId<<")...";
	if(send(socketId, message, length , 0) < 0){
		cout<<"NOK\n";
	}
	else{
		cout<<"OK\n";
	}
	
}


int Socket_server_tcp::acceptCon(){
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLength=sizeof(clientAddress);
	int clientSocket= accept(listenSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
	if(clientSocket>0){
		// Affichage de l'adresse IP du client.
		cout << " accept " << inet_ntoa(clientAddress.sin_addr);
		// Affichage du numéro de port du client.
		cout << ":" << ntohs(clientAddress.sin_port) ;
		cout<<" socket id : "<<clientSocket<< "\n";
	}
	return clientSocket;
	
}
	
Socket_server_tcp::~Socket_server_tcp(){
	cout<<"close socket\n";
	close(listenSocket);
}