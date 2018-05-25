#include "gameattr.h"
#include "eventhandler.h"
#include "gamecomponents.h"
#include "socket.h"

#include <iostream>
#include <stdexcept>

#include <SDL2/SDL.h>

//undefine SDL's main
#ifdef main
#undef main
#endif

#pragma comment(lib, "ws2_32.lib")


SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
ClientSocket* client_socket = nullptr;


void connectToServer();
void initSDL();
void initGame();
void promptPlayerInfo(std::string*, float*, float*);
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
	if(client_socket->isConnected()){
		client_socket->runMsgHandlingThread();
	}else{
		throw std::runtime_error("Failed to connect!");
	}
}

void initSDL(){
	SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");

	//init sdl
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
		throw std::runtime_error("Failed to init SDL!");
	}else; //go on

	//create window
	if((window=SDL_CreateWindow("game window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE)) == nullptr){
		throw std::runtime_error("Failed to create window!");
	}else; //go on

	//create renderer
	if((renderer=SDL_CreateRenderer(window, -1, 0)) == nullptr){
		throw std::runtime_error("Failed to create renderer");
	}else; //go on
}

void initGame(){
	//initiate eventhandler, metadata, and in-game components (through GameComponents).
	std::string name("");
	float x =0.0f;
	float y =0.0f;
	promptPlayerInfo(&name, &x, &y);
	GameComponents::init(window, renderer, client_socket, name, x, y);
}

void promptPlayerInfo(std::string* name, float* x, float* y){
	std::cout<<"What yo box name is?\n";
	std::cin>>*name;
	std::cout<<"Where dat box be at? (specify x&y coords in range of 0.0~1.0)\n";
	std::cin>>*x>>*y;
}

void gameLoop(){
	while(GameAttr::isRunning()){
		//only game loop happens here (update, render). Read/Write through socket is done in separate threads
		EventHandler::update();
		GameAttr::update(window);
		GameComponents::update();
		GameComponents::render();
	}
}

void destroyGame(){
	//free in-game resources
}

void destroySDL(){

}

void disconnectFromServer(){
	client_socket->disconnect();
	delete client_socket;
}
