#include <SDL2/SDL.h>


#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

class EventHandler{
	public:
		enum { W=0, A=1, S=2, D=3 };
		enum Button{ LEFT=0, MID=1, RIGHT=2 };
		enum Axis{ X=0, Y=1 };
	private:
		static struct Keyboard{
			bool pressed[4];
		} keyboard;
		static bool mouse_click[3];
		static bool mouse_held[3];
		static float mouse_pos[2];
		static float mouse_click_pos[3][2];
		static SDL_Event event;
	private:
		EventHandler() = delete;
		~EventHandler() = delete;
		EventHandler(const EventHandler&) = delete;
		EventHandler& operator=(const EventHandler&) = delete;
	public:
		static void update();
		static bool isClicked(int);
		static bool isHeld(int);
		static float getPos(int);
		static float getClickPos(int, int);
		static bool keyPressed(int);
};

#endif
