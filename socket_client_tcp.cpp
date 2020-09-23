////////////////////////////////////////////////////////////////
// Include 
////////////////////////////////////////////////////////////////

#include "socket_client_tcp.h"

using namespace std;
////////////////////////////////////////////////////////////////
// Function
////////////////////////////////////////////////////////////////

Socket_client_tcp::Socket_client_tcp(const unsigned short int serverPort,const char server[]){
	struct hostent *hostInfo;
	
	
	
	cout<<"try to get host info....";
	hostInfo = gethostbyname(server);
	if (hostInfo == NULL) {
		cout<<"NOK \n";
	}
	cout<<"OK\n";
	cout<<"try to create socket....";
	// Création de socket. "AF_INET" correspond à l'utilisation du protocole IPv4
	// au niveau réseau. "SOCK_DGRAM" correspond à l'utilisation du protocole UDP
	// au niveau transport. La valeur 0 indique qu'un seul protocole sera utilisé
	// avec ce socket.
	socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);//SOCK_STREAM for TCP¨- SOCK_DGRAM for UDP
	if (socketDescriptor < 0) {
		cout << "Impossible to create socket\n";
		exit(1);
	}
	cout<<"OK\n";
	// add server information
	serverAddress.sin_family = AF_INET;//IPV4
	memcpy((char *) &serverAddress.sin_addr.s_addr,hostInfo->h_addr_list[0], hostInfo->h_length);//copy server information
	serverAddress.sin_port = htons(serverPort);
	
	socklen_t serverAddressLength=sizeof(serverAddress);
	cout<<"try to connect....";
	if(connect(socketDescriptor,(struct sockaddr*)&serverAddress,serverAddressLength)==-1){
		cout<<"NOK\n";
		exit(1);
		
	}
	cout<<"OK\n";
}

bool Socket_client_tcp::sendM(const char msg[],const unsigned int length){
	cout<<"try to send....";
	if (send(socketDescriptor, msg,length,0) < 0) {
		cout<<"send NOK\n";
		return false;
	
	}
	else{
		cout<<"send OK\n";
		return true;
	}

}


unsigned int Socket_client_tcp::rec(char msg[],const unsigned int length,unsigned int timeout){
	unsigned int numRead=0;
	cout<<"try to receive ....";
	if(timeout>0){
		struct timeval tv;// timeout time
		fd_set readSet;
		FD_ZERO(&readSet);
		FD_SET(socketDescriptor, &readSet);
		tv.tv_sec = timeout;
		tv.tv_usec = 0;
		if (!select(socketDescriptor+1, &readSet, NULL, NULL, &tv)) {// if no message during timeout
			cout<<"timeout ERROR";
			return 0;
		}
	}
	
	
	numRead = recv(socketDescriptor, msg, length, 0);
	cout<<"("<<numRead<<") : "<<msg;
	return numRead;
		

}	
Socket_client_tcp::~Socket_client_tcp(){
	cout<<"close socket\n";
	close(socketDescriptor);
}