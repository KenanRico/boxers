#include "playermanager.h"
#include "player.h"

#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>


PlayerManager::PlayerManager(){
	//do nothing
}

PlayerManager::~PlayerManager(){
	for(std::vector<Player*>::iterator p=players.begin(); p!=players.end(); ++p){
		delete *p;
	}
}

void PlayerManager::setSocket(int ss){
	server_socket = ss;
}

void PlayerManager::addPlayer(){
		Player* new_player = new Player(server_socket, ID_generator);
		if(new_player->isConnected()){
			new_player->startNewThread();
			players.push_back(new_player);
			++ID_generator;
		}else{
			delete new_player;
			throw std::runtime_error("Failed to open socket for new player!");
		}
}
