#include <SDL2/SDL.h>

#ifndef GAME_ATTR_H
#define GAME_ATTR_H

class GameAttr{
	private:
		static bool running;
		static int windowW;
		static int windowH;
		static int current_time;
		static int FPS;
	private:
		GameAttr() = delete;
		~GameAttr() = delete;
		GameAttr(const GameAttr&) = delete;
		GameAttr& operator=(const GameAttr&) = delete;
	public:
		static bool isRunning();
		static int getWindowW();
		static int getWindowH();
		static void stopGame(); //once called, game terminates
		static float normalizedX(int);
		static float normalizedY(int);
		static int physicalX(float);
		static int physicalY(float);
		static void update(SDL_Window*);
};

#endif
