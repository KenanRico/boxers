#include "playermanager.h"
#include "player.h"

#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sstream>
#include <unistd.h>
#include <pthread.h>
#include <iostream>

#define MAX_WAITING_CLIENT 20




PlayerManager::PlayerManager(): server_socket(-1), overall_game_state(""){
	//do nothing
}

PlayerManager::~PlayerManager(){
	pthread_join(wait_thread.ID, nullptr);
	for(std::vector<Player*>::iterator p=players.begin(); p!=players.end(); ++p){
		delete *p;
	}
}

void PlayerManager::setSocket(int ss){
	server_socket = ss;
}

void* waitLoop(void*);

void PlayerManager::startServerSocketThread(){
	pthread_attr_init(&wait_thread.attrib);
	wait_thread.started = (pthread_create(&wait_thread.ID, &wait_thread.attrib, waitLoop, (void*)this)==0);
}

void* waitLoop(void* arg){
	PlayerManager* pm = (PlayerManager*)arg;
	while(true){
		listen(pm->server_socket, MAX_WAITING_CLIENT);
		pm->addPlayer();
	}
	std::cout<<"No longer waiting for clients!\n";
}

void PlayerManager::addPlayer(){
		Player* p = new Player(server_socket, "lool", &overall_game_state);
		if(p->isConnected()){
			p->startNewThread();
			players.push_back(p);
		}else{
			delete p;
			throw std::runtime_error("Failed to open socket for new player!");
		}
}

void PlayerManager::update(){
	//update overall_game_state
	std::stringstream ss;
	for(std::vector<Player*>::iterator p=players.begin(); p!=players.end(); ++p){
		ss<<(*p)->player.name<<":"<<(*p)->player.x<<","<<(*p)->player.y<<" ";
	}
	overall_game_state = ss.str();
}
