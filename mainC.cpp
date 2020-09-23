////////////////////////////////////////////////////////////////
// Include
////////////////////////////////////////////////////////////////
#include <iostream>

#include "socket_client_udp.h"
#include "socket_client_tcp.h"

////////////////////////////////////////////////////////////////
// Macro
////////////////////////////////////////////////////////////////
#define MSG_LENGTH_MAX 50



using namespace std;

////////////////////////////////////////////////////////////////
// Function
////////////////////////////////////////////////////////////////
void* app(void* arg){
	char msg[MSG_LENGTH_MAX]="test send";//msg to send to server
	Socket_client_tcp client(8080,"localhost");
	
	if(client.sendM(msg,strlen(msg))){
		if(client.rec(msg,MSG_LENGTH_MAX,10)!=0){
			cout<<"message recu : "<<msg<<"\n";
		}
		else{
			cout<<"no message recive\n";
		}
		
		
	}
	else{
			cout<<"no message send\n";
	}
	
	
}


/**
@brief main function 
**/

int main(int argc, char *argv[]){
	char msg[MSG_LENGTH_MAX]="test send";//msg to send to server
	cout<<"main Client start\n";
	
	//UDP
	/*
	Socket_client_udp client(8080,"localhost");
	
	if(client.send(msg,strlen(msg))){
		if(client.rec(msg,MSG_LENGTH_MAX,5)!=0){
			cout<<"message recu : "<<msg<<"\n";
		}
		else{
			cout<<"no message recive\n";
		}
		
		
	}
	else{
			cout<<"no message send\n";
	}
	*/
	
	//TCP

	/*
	Socket_client_tcp client(8080,"localhost");
	
	if(client.sendM(msg,strlen(msg))){
		if(client.rec(msg,MSG_LENGTH_MAX,5)!=0){
			cout<<"message recu : "<<msg<<"\n";
		}
		else{
			cout<<"no message recive\n";
		}
		
		
	}
	else{
			cout<<"no message send\n";
	}
	*/
	//TCP Thread
	pthread_t threadId[30];//create threadId array
	
	for(unsigned int i=0;i<30;i++){
		if(pthread_create(&threadId[i], NULL,app, NULL) != 0 ){
			cout<<"\t ERROR create thread_n";
		}
	}
	for(unsigned int i=0;i<30;i++){//wait all thread finish
		pthread_join(threadId[i],NULL);
	}
	
	
	
	
}