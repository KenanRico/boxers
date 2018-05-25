#include "box.h"
#include "gameattr.h"

#include <string>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <SDL2/extensions/SDL_image.h>



Box::Box(std::string n, float _x, float _y, SDL_Renderer* r): name(n), x(_x), y(_y), texture(nullptr){
	//create texture
	SDL_Surface* surface = IMG_Load("assets/ninja.png");
	if(surface==nullptr){
		throw std::runtime_error("Failed to load surface!");
	}else;
	texture = SDL_CreateTextureFromSurface(r, surface);
	if(texture==nullptr){
		throw std::runtime_error("Failed to load texture!");
	}else;
	SDL_FreeSurface(surface);
	
	//set src rectangle
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(texture, 0, 0, &src.w, &src.h);

	//set dest rectangle
	dest.x = GameAttr::physicalX(x);
	dest.y = GameAttr::physicalY(y);
	dest.w = GameAttr::physicalX(0.06);
	dest.h = GameAttr::physicalY(0.06);
}

Box::~Box(){
	SDL_DestroyTexture(texture);
}




void Box::moveX(float deltax){
	x+=deltax;
	dest.x = GameAttr::physicalX(x);
}

void Box::moveY(float deltay){
	y+=deltay;
	dest.y = GameAttr::physicalY(y);
}

void Box::setX(float new_x){
	x = new_x;
	dest.x = GameAttr::physicalX(x);
}

void Box::setY(float new_y){
	y = new_y;
	dest.y = GameAttr::physicalY(y);
}

std::string Box::getName() const{
	return name;
}

void Box::render(SDL_Renderer* renderer){
	SDL_RenderCopy(renderer, texture, &src, &dest);
}
