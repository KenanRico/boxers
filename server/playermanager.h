#include "player.h"

#include <vector>
#include <string>


#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

class PlayerManager{
	private:
		std::vector<Player*> players;
		int server_socket;
		//game's overall state in the form of a string that gets updated whenever a player client's state changes. 
		//Whenever this string gets updated, it gets broadcasted to all players
		std::string overall_game_state;
	
	public:
		PlayerManager();
		~PlayerManager();
	private:
		PlayerManager(const PlayerManager&) = delete;
		PlayerManager& operator=(const PlayerManager&) = delete;

	public:
		void setSocket(int);
		void addPlayer();
		void update();
};

#endif
