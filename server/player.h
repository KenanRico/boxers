#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>



#ifndef PLAYER_H
#define PLAYER_H

class Player{
	private:
		//player state, updated on each message received from player client
		struct PlayerInfo{
			int ID;
			float x;
			float y;
		} player;
		//socket information used to connect to player client
		struct SocketInfo{
			int sock;
			struct sockaddr_in addr;
			socklen_t length;
			bool connected;
		} socket;
		//communication thread related info
		struct ThreadInfo{
			pthread_t ID;
			pthread_attr_t attrib;
			bool started;
		} thread;

	public:
		Player(int, int);
		~Player();
	private:
		Player() = delete;
		Player(const Player&) = delete;
		Player& operator=(const Player&) = delete;

	public:
		bool isConnected() const;
		void startNewThread();


	friend class PlayerManager;
	friend void* communicationHandler(void* arg);
};

#endif
