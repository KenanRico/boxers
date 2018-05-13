#include "player.h"

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>


Player::Player(int server_socket, int player_ID): player((struct PlayerInfo){player_ID,0.0f,0.0f}){
	thread.ID = -1;
	thread.started = false;
	socket.length = sizeof(socket.addr);
	//attempt to open new socket
	if((socket.sock = accept(server_socket, (struct sockaddr*)&(socket.addr), &socket.length)) >= 0){
		std::cout<<"Player connection established\n";
		socket.connected = true;
	}else{
		std::cerr<<"errno:"<<errno<<"\n";
		socket.connected = false;
	}
}

Player::~Player(){
	//close socket?

	//wait for comm thread
	//dont throw exceptions here
	if(thread.started){
		if(pthread_join(thread.ID, nullptr)==0){
			std::cout<<"Comm thread successfully ended\n";
		}else{
			std::cerr<<"Error while waiting for comm thread! (unknown error)\n";
		}
	}else{
		std::cerr<<"Error while waiting for comm thread! (thread did not start successfully)\n";

	}
}

bool Player::isConnected() const{
	return socket.connected;
}

void* communicationHandler(void* arg){
	Player* p = (Player*)arg;
	while(p->socket.connected){
		char msg[256];
		ssize_t N = read(p->socket.sock, msg, 255);
		if(N>=0){
			//update player.x and player.y (needs to be guarded with mutex)
			std::cout<<msg<<"\n";
		}else;
	}
	pthread_exit(nullptr);
	return nullptr;
}

void Player::startNewThread(){
	pthread_attr_init(&thread.attrib);
	thread.started = (pthread_create(&thread.ID, &thread.attrib, communicationHandler, (void*)this)==0);
}
