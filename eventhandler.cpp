#include "eventhandler.h"
#include "gameattr.h"

#include <stdexcept>
#include <iostream>

#include <SDL2/SDL.h>



bool EventHandler::mouse_click[3];
bool EventHandler::mouse_held[3];
float EventHandler::mouse_pos[2];
float EventHandler::mouse_click_pos[3][2];
SDL_Event EventHandler::event;

void EventHandler::update(){
	mouse_click[LEFT] = false;
	mouse_click[MID] = false;
	mouse_click[RIGHT] = false;
	
	if(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				GameAttr::stopGame();
				break;
			case SDL_MOUSEMOTION:
				mouse_pos[X] = event.motion.x;
				mouse_pos[Y] = event.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse_click[event.button.button-1] = true;
				mouse_held[event.button.button-1] = true;
				mouse_click_pos[event.button.button-1][X] = event.motion.x;
				mouse_click_pos[event.button.button-1][Y] = event.motion.y;
				//std::cout<<"x:"<<mouse_pos[0]<<" y:"<<mouse_pos[1]<<" button:"<<(int)event.button.button<<"\n";
				break;
			case SDL_MOUSEBUTTONUP:
				mouse_held[event.button.button-1] = false;
				//std::cout<<mouse_held[LEFT]<<"\n";
				break;
			default:
				break;
		}
	}else{
		//no events
	}
}

bool EventHandler::isClicked(int button){
	if(button!=LEFT && button!=MID && button!=RIGHT){
		throw std::runtime_error("No such button!");
	}
	return mouse_click[button];
}

bool EventHandler::isHeld(int button){
	if(button!=LEFT && button!=MID && button!=RIGHT){
		throw std::runtime_error("No such button!");
	}else;
	return mouse_held[button];
}

float EventHandler::getPos(int axis){
	if(axis!=X && axis!=Y){
		throw std::runtime_error("No such axis!");
	}
	return mouse_pos[axis];
}

float EventHandler::getClickPos(int button, int axis){
	if((button!=LEFT&&button!=MID&&button!=RIGHT) || (axis!=X&&axis!=Y)){
		throw std::runtime_error("Button or axis be invalid famo!");
	}else;
	return mouse_click_pos[button][axis];
}


