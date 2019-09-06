#include "stdafx.h"
#include "TextureManager.h"


TextureManager::TextureManager()
{
	
}


TextureManager::~TextureManager()
{
	delete singleText;
}


bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* Renderer)       
{
	std::cout << "Texture" << id << " start load" << std::endl;
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());                              //�������� ����������� �� ����� � Surface
	if (pTempSurface == 0)
	{
		std::cout << "Texture from file" << id << " not load" << std::endl;
		return false;                                                                    //���� �������� �� ��������� �� �����
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Renderer, pTempSurface);        //������������ ��������� 
	SDL_FreeSurface(pTempSurface);                                                       //������������ Surface
	if (pTexture != 0)                                                                   //�������� ������� ��������
	{
		textureMap[id] = pTexture;                                                       //���� ������� ���� �� �������� ������������ � ���������
		std::cout << "Texture" << id << " load successful" << std::endl;
		return true;
	}
	else
	{
		std::cout << "Texture"<<id<< " not create"<< std::endl;
	}
	return false;
}
void TextureManager::draw(std::string id, int x, int y, int width, int height,
	SDL_Renderer* Renderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;                                                                    //���������� ������������ �������� � ���� 
	SDL_Rect destRect;                                                                   //���������� ������������ �������� ����������� ����� �������
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(Renderer, textureMap[id], &srcRect, &destRect, 0, 0, flip);         //�������� ������� � ������ ��� ����������� � ����
}
void TextureManager::drawScale(std::string id, int x, int y, int width, int height, int dWidth, int dHeight,
	SDL_Renderer* Renderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;                                                                    //���������� ������������ �������� � ���� 
	SDL_Rect destRect;                                                                   //���������� ������������ �������� ����������� ����� �������
	srcRect.x = 0;
	srcRect.y = dWidth;
	srcRect.w = 8;
	srcRect.h = 6;
	destRect.w = width;
	destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(Renderer, textureMap[id], &srcRect, &destRect, 0, 0, flip);         //�������� ������� � ������ ��� ����������� � ����
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height,
	int currentRow, int currentFrame, SDL_Renderer *Renderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;                                                                    //���������� ������������ �������� � ���� 
	SDL_Rect destRect;                                                                   //���������� ������������ �������� ����������� ����� �������
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(Renderer, textureMap[id], &srcRect, &destRect, 0, 0, flip);          //�������� ������� � ������ ��� ����������� � ����
}

void TextureManager::drawWithRotate(std::string id, int x, int y, int width, int height, SDL_Renderer * Renderer, double angle, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;                                                                    //���������� ������������ �������� � ���� 
	SDL_Rect destRect;                                                                   //���������� ������������ �������� ����������� ����� �������
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(Renderer, textureMap[id], &srcRect, &destRect, angle, 0, flip);         //�������� ������� � ������ ��� ����������� � ����

}

void TextureManager::drawVertical(std::string id, int x, int y, int width, int height, SDL_Renderer * Renderer,double angle)
{
	SDL_Rect srcRect;                                                                    //���������� ������������ �������� � ���� 
	SDL_Rect destRect;   
	SDL_Point point;//���������� ������������ �������� ����������� ����� �������
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	point.x = width/4;
	point.y = height/2;
	SDL_RenderCopyEx(Renderer, textureMap[id], &srcRect, &destRect, angle, &point, SDL_FLIP_NONE);         //�������� ������� � ������ ��� ����������� � ����
}

void TextureManager::WriteText(std::string id, SDL_Renderer* Renderer, char* text, int size, Uint8 r, Uint8 g, Uint8 b)
{
	TTF_Font* Sans = TTF_OpenFont("Fontss/constan.ttf", size); //this opens a font style and sets a size
	SDL_Color color;
	if((r<=255) && (r >= 0) && (g >= 0) &&(g <= 255) && (b >= 0) &&(b<= 255))
		color = { r, g, b };  
	else color = { 0,0,0 };

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text, color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Renderer, surfaceMessage); //now you can convert it into a texture
	if (Message != 0)                                                                   //�������� ������� ��������
	{
		textMap[id] = Message;                                                       //���� ������� ���� �� �������� ������������ � ���������
		textParam[id].width = surfaceMessage->w;
		textParam[id].height = surfaceMessage->h;
	}
	else
	{
		std::cout << "Texture" << id << " not load" << std::endl;
	}
}

void TextureManager::DrawText(std::string id, SDL_Renderer * Renderer, int x, int y)
{
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = x;  //controls the rect's x coordinate 
	Message_rect.y = y; // controls the rect's y coordinte
	Message_rect.w = textParam[id].width; // controls the width of the rect
	Message_rect.h = textParam[id].height; // controls the height of the rect
	SDL_RenderCopy(Renderer, textMap[id], NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
}

void TextureManager::loadSingleText(char* text,int size, SDL_Renderer * Renderer)
{
	TTF_Font* Sans = TTF_OpenFont("Fontss/constan.ttf", size); //this opens a font style and sets a size
	SDL_Color color;
	
	color = { 255,255,255 };

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text, color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Renderer, surfaceMessage); //now you can convert it into a texture
	if (Message != 0)                                                                   //�������� ������� ��������
	{
		singleText = Message;                                                       //���� ������� ���� �� �������� ������������ � ���������
		mWidth = surfaceMessage->w;
		mHeight = surfaceMessage->h;
	}
	else
	{
		std::cout << "Texture singleText not load" << std::endl;
	}
}

void TextureManager::drawSingleText(SDL_Renderer * Renderer, int x, int y)
{
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = x;  //controls the rect's x coordinate 
	Message_rect.y = y; // controls the rect's y coordinte
	Message_rect.w = mWidth; // controls the width of the rect
	Message_rect.h = mHeight; // controls the height of the rect
	SDL_RenderCopy(Renderer, singleText, NULL, &Message_rect);
}

void TextureManager::DeleteTexture(std::string id)
{
	textureMap.erase(id);
}
