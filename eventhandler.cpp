#include "eventhandler.h"
#include "gameattr.h"

#include <stdexcept>
#include <iostream>

#include <SDL2/SDL.h>


struct EventHandler::Keyboard EventHandler::keyboard;
bool EventHandler::mouse_click[3];
bool EventHandler::mouse_held[3];
float EventHandler::mouse_pos[2];
float EventHandler::mouse_click_pos[3][2];
SDL_Event EventHandler::event;



void EventHandler::update(){

	//reset mouse
	mouse_click[LEFT] = false;
	mouse_click[MID] = false;
	mouse_click[RIGHT] = false;

	//reset keyboard
	keyboard.pressed[W] = false;
	keyboard.pressed[A] = false;
	keyboard.pressed[S] = false;
	keyboard.pressed[D] = false;

	
	if(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				GameAttr::stopGame();
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_w: keyboard.pressed[W] = true; break;
					case SDLK_a: keyboard.pressed[A] = true; break;
					case SDLK_s: keyboard.pressed[S] = true; break;
					case SDLK_d: keyboard.pressed[D] = true; break;
					default: break;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym){
					case SDLK_w: keyboard.pressed[W] = false; break;
					case SDLK_a: keyboard.pressed[A] = false; break;
					case SDLK_s: keyboard.pressed[S] = false; break;
					case SDLK_d: keyboard.pressed[D] = false; break;
					default: break;
				}
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

bool EventHandler::keyPressed(int k){
	return keyboard.pressed[k];
}

