#include "playermanager.h"
#include "player.h"

#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sstream>
#include <unistd.h>


PlayerManager::PlayerManager(): server_socket(-1), overall_game_state(""){
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
		Player* p = new Player(server_socket, "?", &overall_game_state);
		if(p->isConnected()){
			//get player ID
			char msgarr[256];
			ssize_t N = read(p->socket.sock, msgarr, 255);
			if(N>=0){
				std::string msg(msgarr);
				std::stringstream(msg)>>p->player.name;
			}else;
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
