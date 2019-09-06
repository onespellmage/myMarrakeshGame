#pragma once
#include "SDL_Setup.h"
#include "TextureManager.h"
#include "Field.h"
#define fps 60

enum State
{
	menu,
	processS,
	score
};

enum FocusButton
{
	START,
	PLAYER,
	EXIT,
	FIELD,
	ACCEPT,
	OK_SCORE,
	NONE

};
enum ProcessStep
{
	AsamDir=1,
	DropDice=2,
	AsamMove=3,
	Payment=4,
	SetCarpet=5
};

class GMain
{
public:
	GMain();
	~GMain();
	void init();
	void draw();
	void mainLoop();
	void mouseAction();
	void process();
	void onFocus(int x, int y);
	void drawMessage();
private:
	short int playerNum;
	int mass[49];
	int posChar;
	int step;
	int numPlayer;
	bool Lock;
	CSDL_Setup* csdl_setup;
	TextureManager* Texture;
	bool quit;
	int MouseX;
	int MouseY;
	Uint32 starting_tick;

	State state;
	ProcessStep steps;
	FocusButton focusButton;
	Field field;

	//ТЕСТ(удалить)
	int speedX;
	int hasteX;
	int hasteY;
	int speedY;
	int deltaX;
	int deltaY;
	double angle;
	SDL_RendererFlip flipType;
	std::string str;
	short currentPl;

	int xSize;
	int ySize;
};

