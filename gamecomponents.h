#include "socket.h"
#include "box.h"

#include <map>

#include <SDL2/SDL.h>


#ifndef GAME_COMPONENTS_H
#define GAME_COMPONENTS_H

class GameComponents{
	private:
		static SDL_Window* window;
		static SDL_Renderer* renderer;
		static bool updated;
		static Box* box; //local player character
		static std::map<std::string, Box*> other_boxes; //other players
		static ClientSocket const * socket;
	private:
		GameComponents() = delete;
		~GameComponents() = delete;
		GameComponents(const GameComponents&) = delete;
		GameComponents& operator=(const GameComponents&) = delete;
	public:
		static void init(SDL_Window*, SDL_Renderer*, ClientSocket*, std::string, float, float);
		static void update();
		static void render();
		static void destroy();
};

#endif
