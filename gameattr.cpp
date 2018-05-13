#include "gameattr.h"

#include <SDL2/SDL.h>


bool GameAttr::running = true;
int GameAttr::windowW = 800; //default width
int GameAttr::windowH = 600; //default height
int GameAttr::current_time = 0;
int GameAttr::FPS = 60;

bool GameAttr::isRunning(){
	return running;
}

int GameAttr::getWindowW(){
	return windowW;
}

int GameAttr::getWindowH(){
	return windowH;
}

void GameAttr::stopGame(){
	running = false;
}

float GameAttr::normalizedX(int x){
	return (float)x/(float)windowW;
}
float GameAttr::normalizedY(int y){
	return (float)y/(float)windowH;
}

int GameAttr::physicalX(float x){
	return (int)(x * windowW);
}
int GameAttr::physicalY(float y){
	return (int)(y * windowH);
}

void GameAttr::update(SDL_Window* window){
	//update window parameters
	SDL_GetWindowSize(window, &windowW, &windowH);

	//frame limiting
	int delta_time = SDL_GetTicks() - current_time;
	int delay_time = 1000/FPS - delta_time;
	if(delay_time>0){
		//delay delay_time ms
		SDL_Delay(delay_time);
	}else{
		//do nothing
	}
}
