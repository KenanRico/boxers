
#include <string>

#include <SDL2/SDL.h>



#ifndef BOX_H
#define BOX_H

class Box{
	private:
		std::string name;
		float x;
		float y;
		SDL_Texture* texture;
		SDL_Rect src;
		SDL_Rect dest;

	public:
		Box(std::string, float, float, SDL_Renderer*);
		~Box();
	private:
		Box() = delete;
		Box(const Box&) = delete;
		Box& operator=(const Box&) = delete;

	public:
		void moveX(float);
		void moveY(float);
		void setX(float);
		void setY(float);
		float getX() const;
		float getY() const;
		std::string getName() const;
		
		void render(SDL_Renderer*);

};

#endif
