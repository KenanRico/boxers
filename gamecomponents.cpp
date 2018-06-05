#include "gamecomponents.h"
#include "eventhandler.h"
#include "box.h"

#include <map>
#include <sstream>
#include <algorithm>

#include <SDL2/SDL.h>


bool GameComponents::updated = false;
SDL_Window* GameComponents::window = nullptr;
SDL_Renderer* GameComponents::renderer = nullptr;
Box* GameComponents::box = nullptr;
std::map<std::string, Box*> GameComponents::other_boxes;
ClientSocket const * const * GameComponents::socket = nullptr;


void GameComponents::init(SDL_Window* w, SDL_Renderer* r, ClientSocket** s, std::string n, float x, float y){
	window = w;
	renderer = r;
	socket = (ClientSocket const * const *)s;
	box = new Box(n, x, y, renderer);
}

void GameComponents::update(){

	//reset update state
	updated = false;

	//update local player
	if(EventHandler::keyPressed(EventHandler::W)){
		box->moveY(-0.001f);
		updated = true;
	}else;
	if(EventHandler::keyPressed(EventHandler::A)){
		box->moveX(-0.001f);
		updated = true;
	}else;
	if(EventHandler::keyPressed(EventHandler::S)){
		box->moveY(0.001f);
		updated = true;
	}else;
	if(EventHandler::keyPressed(EventHandler::D)){
		box->moveX(0.001f);
		updated = true;
	}else;

	//update other players
	std::stringstream new_msg_ss((*socket)->getCurrentMessage());
	std::string b("");
	while(new_msg_ss>>b){
		//b should be in the format of "playername:x,y", transform it into "playername x y"
		replace(b.begin(), b.end(), ':', ' ');
		replace(b.begin(), b.end(), ',', ' ');
		//parse b into 3 parts
		std::string name = 0;
		float x = 0.0f;
		float y = 0.0f;
		std::stringstream(b)>>name>>x>>y;
		//assign new values to proper boxes
		if(name==box->getName()){
			//do nothing
		}else if(other_boxes.find(name)!=other_boxes.end()){
			other_boxes.find(name)->second->setX(x);
			other_boxes.find(name)->second->setY(y);
		}else{
			other_boxes.insert(std::make_pair(name, new Box(name, x, y, renderer)));
		}
	}
}

void GameComponents::render(){
	SDL_RenderClear(renderer);
	box->render(renderer);
	for(std::map<std::string, Box*>::iterator i=other_boxes.begin(); i!=other_boxes.end(); ++i){
		i->second->render(renderer);
	}
	SDL_RenderPresent(renderer);
}

void GameComponents::destroy(){
	delete box;
	for(std::map<std::string, Box*>::iterator i=other_boxes.begin(); i!=other_boxes.end(); ++i){
		delete i->second;
	}
}

bool GameComponents::isUpdated(){
	return updated;
}

Box const * GameComponents::getMyBox(){
	return box;
}
