#include "player.h"

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>


Player::Player(int server_socket, std::string player_name, std::string* ogs): player((struct PlayerInfo){player_name,0.0f,0.0f}), overall_game_state(ogs){
	//temp write thread info
	write_thread.ID = -1;
	write_thread.started = false;
	//temp write thread info
	read_thread.ID = -1;
	read_thread.started = false;
	//attempt to open new socket
	socket.length = sizeof(socket.addr);
	if((socket.sock = accept(server_socket, (struct sockaddr*)&(socket.addr), &socket.length)) >= 0){
		std::cout<<"Player connection established\n";
		socket.connected = true;
		//get player ID
		char msgarr[256];
		memset(msgarr, 0, sizeof(msgarr));
		ssize_t N = read(socket.sock, msgarr, 255);
		if(N>=0){
			std::string msg(msgarr);
			std::stringstream(msg)>>player.name;
			std::cout<<"name: "<<msg<<"\n";
		}else;
	}else{
		std::cerr<<"errno:"<<errno<<"\n";
		socket.connected = false;
	}
}

Player::~Player(){
	//close socket?

	//wait for comm thread
	//dont throw exceptions here
	if(write_thread.started && read_thread.started){
		if(pthread_join(write_thread.ID, nullptr)==0 && pthread_join(read_thread.ID, nullptr)==0){
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


void* writeRoutine(void*);
void* readRoutine(void*);

void Player::startNewThread(){
	pthread_attr_init(&write_thread.attrib);
	pthread_attr_init(&read_thread.attrib);
	
	write_thread.started = (pthread_create(&write_thread.ID, &write_thread.attrib, writeRoutine, (void*)this)==0);
	read_thread.started = (pthread_create(&read_thread.ID, &read_thread.attrib, readRoutine, (void*)this)==0);
}

void* writeRoutine(void* arg){
	Player* p = (Player*)arg;
	while(p->socket.connected){
		//configure overall_game_state
		//write overall_game_state through socket
		std::cout<<*(p->overall_game_state)<<"\n";
		write(p->socket.sock, p->overall_game_state->c_str(), p->overall_game_state->size());
	}
}

void* readRoutine(void* arg){
	Player* p = (Player*)arg;
	while(p->socket.connected){
		char msgarr[256];
		memset(msgarr, 0, sizeof(msgarr));
		ssize_t N = read(p->socket.sock, msgarr, 255);
		if(N>=0){
			//parse message for new x and y, and update player x and y
			std::string msg(msgarr);
			std::stringstream(msg)>>p->player.x>>p->player.y;
			//std::cout<<msg<<"\n";
		}else;
	}
	pthread_exit(nullptr);
	return nullptr;
}
