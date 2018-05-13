#include "player.h"
#include "playermanager.h"

#include <iostream>
#include <stdexcept>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <vector>
#include <string>

#define MAX_WAITING_CLIENT 20



int server_socket = -1;
struct sockaddr_in server_addr;
PlayerManager players;

void createServerSocket();
void bindServerSocket();
void acceptPlayerConnections();
void closeServerSocket();



int main(){
	try{
		createServerSocket();
		bindServerSocket();
		acceptPlayerConnections();
		closeServerSocket();
	}catch(const std::exception& e){
		std::cout<<e.what()<<"\n";
	}
	return 0;
}

void createServerSocket(){
	if((server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))>=0){
		std::cout<<"Created server socket!\n";
	}else{
		throw std::runtime_error("Unable to create server socket!");
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(1500);
}

void bindServerSocket(){
	if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))>=0){
		std::cout<<"Bound server socket!\n";
		//let player manager know socket info
		players.setSocket(server_socket);
	}else{
		throw std::runtime_error("Unable to bind server socket!");
	}
}

void acceptPlayerConnections(){
	//main loop
	while(true){
		listen(server_socket, MAX_WAITING_CLIENT);
		players.addPlayer();
	}
	std::cout<<"No longer waiting for clients!\n";
}

void closeServerSocket(){
	//for(std::vector<Player*>::iterator iter=players.begin(); iter!=players.end(); ++iter){
	//	delete *iter;
	//}
}

