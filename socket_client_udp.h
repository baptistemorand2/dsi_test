#ifndef SOCKET_CLIENT_UDP__H
#define SOCKET_CLIENT_UDP__H



////////////////////////////////////////////////////////////////
//////// Include
////////////////////////////////////////////////////////////////
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <iostream>
#include <netdb.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


////////////////////////////////////////////////////////////////
/////// Macro
////////////////////////////////////////////////////////////////
/**
@brief port of the server
**/
#define DEFAULT_PORT 8000
#define DEFAULT_SERVER "127.0.0.1"//localhost

////////////////////////////////////////////////////////////////
////// Function
////////////////////////////////////////////////////////////////

/**
@brief client class 
**/
class Socket_client_udp{
	public:
		/**
		@brief client constructor
		@param serverPort port of the socket
		@param server ip or hostname of the broker
		**/
		Socket_client_udp(const unsigned short int serverPort=DEFAULT_PORT,const char server[]=DEFAULT_SERVER);
		/**
		@brief send to server
		@param msg msg to send
		@param length length of msg
		@return true if msg send else false
		**/
		bool send(const char msg[],const unsigned int length);
		
		
		
		/**
		@brief receive from server
		@param msg msg to send
		@param length length of msg
		@param timeout timeout (0 for no timeout)
		@return 0 if no message else number of byte read
		**/
		unsigned int rec(char msg[],const unsigned int length,unsigned int timeout=5);
		/**
		@brief client destructor
		**/		
		~Socket_client_udp();

		
	private:
		/**
		@brief socket descriptor
		**/
		int socketDescriptor;
		/**
		@brief information of server
		**/
		struct sockaddr_in serverAddress;

	
};





#endif