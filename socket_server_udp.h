#ifndef SOCKET_SERVER_UDP__H
#define SOCKET_SERVER_UDP__H


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
#include <arpa/inet.h>


////////////////////////////////////////////////////////////////
/////// Macro
////////////////////////////////////////////////////////////////
/**
@brief default port of the server
**/
#define DEFAULT_PORT 8000


////////////////////////////////////////////////////////////////
////// Function
////////////////////////////////////////////////////////////////

/**
@brief server class 
**/
class Socket_server_udp{
	public:
		/**
		@brief Socket_server_udp constructor
		@param listenPort port of the socket
		**/
		Socket_server_udp(const unsigned short int listenPort=DEFAULT_PORT);

		/**
		@brief create a listener on socket
		@param maximum length length of the queue
		**/
		void listenS(const unsigned int length);
		
		/**
		@brief check if new message and display it
		@param message message send by the client
		@param maximum length length of the queue
		@return client struct
		**/
		void recv(struct sockaddr_in* clientAddress,char message[],const unsigned int length);
		
		
		/**
		@brief send message
		@param message message send by the client
		@param maximum length length of the queue
		**/
		void send(const struct sockaddr_in clientAddress,char message[],const unsigned int length);
		
		/**
		@brief client destructor
		**/		
		~Socket_server_udp();
		
	private:
		int listenSocket;

	
};





#endif