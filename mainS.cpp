////////////////////////////////////////////////////////////////
// Include
////////////////////////////////////////////////////////////////
#include <iostream>
#include <pthread.h>

#include "socket_server_udp.h"
#include "socket_server_tcp.h"
////////////////////////////////////////////////////////////////
// Macro
////////////////////////////////////////////////////////////////
#define MSG_LENGTH_MAX 50
#define NB_THREAD_MAX 50

////////////////////////////////////////////////////////////////
// Global
////////////////////////////////////////////////////////////////
using namespace std;


pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;


struct arg_struct {
    Socket_server_tcp* server;
    int socketId;
};
////////////////////////////////////////////////////////////////
// Function
////////////////////////////////////////////////////////////////
/**
@brief app process of socket 
**/
void* app(void* arg){
	//pthread_mutex_lock(&mymutex);
	char msgT[MSG_LENGTH_MAX];
	struct arg_struct* socketInfo=(arg_struct*)arg;
	socketInfo->server->recvM(socketInfo->socketId,msgT,MSG_LENGTH_MAX);
	strcat(msgT," return \n");
	cout<<"send msg";
	socketInfo->server->sendM(socketInfo->socketId,msgT,MSG_LENGTH_MAX);
	close(socketInfo->socketId);
	//pthread_mutex_unlock(&mymutex);
	return NULL;
	
	
}

/**
@brief main function 
**/

int main(int argc, char *argv[]){
	char msg[MSG_LENGTH_MAX];
	cout<<"main Server start\n";
	// UDP
	/*
	Socket_server_udp server(8080);// create server on default port 
	server.listenS(5);
	//for each connection create socket 
	while(1){
		struct sockaddr_in client;
		
		server.recv(&client,msg,MSG_LENGTH_MAX);
	
		strcat(msg," return \n");
		server.send(client,msg,strlen(msg));
		
		
		
	}
	*/
	// TCP
	/*
	Socket_server_tcp server(8080);// create server on default port 
	server.listenS(5);// accept 5 connection 
	while(1){
		
		int socket=server.acceptCon();// accept con of client
		if(socket>0){//check if there is a client
				server.recvM(socket,msg,MSG_LENGTH_MAX);
				strcat(msg," return \n");
				server.sendM(socket,msg,MSG_LENGTH_MAX);
				closeSocket(socket);
		}
		
	}
	
	return 0;
	*/
	
	// TCP multithread
	pthread_t threadId[NB_THREAD_MAX];//create threadId array
	int indice=0;
	
	Socket_server_tcp server(8080);// create server on default port 
	server.listenS(NB_THREAD_MAX);// accept 5 connection 
	bool allThreadUse=false;
	while(1){
		
		int socket=server.acceptCon();// accept con of client
		if(socket>0){//check if there is a client
			struct arg_struct args;
			args.server = &server;
			args.socketId = socket;
			if(allThreadUse==true){
				cout<<"wiat thread finish\n";
				pthread_join(threadId[indice],NULL);//wait if thread finish 
			}
			if(pthread_create(&threadId[indice], NULL,app, &args) != 0 ){
				//printf("Failed to create thread\n");
				cout<<"Failed to create thread\n";
				indice--;
			}
			else{
				cout<<"thread create"<<indice<<"\n";
			}
			indice++;
			if(indice>=NB_THREAD_MAX){
				allThreadUse=true;	
				indice=0;
				cout<<"all thread use \n";
				
			}
			
			
			
				//server.recvM(socket,msg,MSG_LENGTH_MAX);
				//strcat(msg," return \n");
				//server.sendM(socket,msg,MSG_LENGTH_MAX);
		}
		
	}
}