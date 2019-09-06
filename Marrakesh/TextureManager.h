#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <map>

struct WHParam
{
	int width;
	int height;
};

class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	                              
	bool load(std::string fileName, std::string id, SDL_Renderer* Renderer);         //загрузка текстуры в контейнер

	void draw(std::string id, int x, int y, int width, int height, 
		SDL_Renderer* Renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);    //отрисовка текстуры на экране
	void drawScale(std::string id, int x, int y, int width, int height, int dWidth, int dHeight,
		SDL_Renderer* Renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height, 
		int currentRow, int currentFrame, SDL_Renderer* Renderer,
		SDL_RendererFlip flip = SDL_FLIP_NONE);                            //отрисовка анимации(спрайта)
	void drawWithRotate(std::string id, int x, int y, int width, int height,
		SDL_Renderer* Renderer, double angle, SDL_RendererFlip flip);
	void drawVertical(std::string id, int x, int y, int width, int height,
		SDL_Renderer* Renderer, double angle);
	void WriteText(std::string id, SDL_Renderer* Renderer, char* text, int size, Uint8 r, Uint8 g, Uint8 b);
	void DrawText(std::string id, SDL_Renderer* Renderer, int x, int y);

	void loadSingleText(char* text, int size, SDL_Renderer * Renderer);
	void drawSingleText(SDL_Renderer * Renderer, int x, int y);

	void DeleteTexture(std::string id);


private:

	std::map<std::string, SDL_Texture*> textureMap;     
	std::map<std::string, SDL_Texture*> textMap;  //контейнера текстур
	std::map<std::string, WHParam> textParam;
	SDL_Texture* singleText;
	int mWidth;
	int mHeight;
};

