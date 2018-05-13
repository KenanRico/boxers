#include "gameattr.h"
#include "eventhandler.h"
#include "socket.h"

#include <iostream>
#include <stdexcept>

#include <SDL2/SDL.h>

//undefine SDL's main
#ifdef main
#undef main
#endif

#pragma comment(lib, "ws2_32.lib")



ClientSocket* client_socket = nullptr;


void connectToServer();
void initSDL();
void initGame();
void gameLoop();
void destroyGame();
void destroySDL();
void disconnectFromServer();



int main(){
	try{
		connectToServer();
		initSDL();
		initGame();
		gameLoop();
		destroyGame();
		destroySDL();
	}catch(const std::exception& e){
		std::cout<<e.what()<<"\n";
	}


	return 0;
}


void connectToServer(){
	ClientSocket::init();
	client_socket = new ClientSocket("127.0.0.1", 1500);
	client_socket->connectToServer();
}

void initSDL(){

}

void initGame(){

}

void gameLoop(){

}

void destroyGame(){

}

void destroySDL(){

}

void disconnectFromServer(){
	client_socket->disconnect();
	delete client_socket;
}
