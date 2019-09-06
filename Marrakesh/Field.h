#pragma once
#include "TextureManager.h"

enum Direction
{
	North = 3,
	East = 0,
	West = 2,
	South = 1,
	None=-1
};

struct Carpet
{
	int player;
	int posX;
	int posY;
	Direction carpetDir;
};

class Field
{
public:
	void setNewGameParam();
	void setSelectPos();
	void setCountPlayer(int count);
	Direction getFocusDir();
	void ClickAction(short act);
	bool Accept(short step);
	void CancelDir();
	void CancelCarpet();
	bool dropDice();
	bool moveAsam();
	void payment();
	void countPayment( int current, int color);
	
	void drawCarpetDir(TextureManager* texture, SDL_Renderer* render);
	void drawDirArrows(TextureManager* texture,SDL_Renderer* render);
	void drawField(TextureManager* texture, SDL_Renderer* render);
	void loadGametext(TextureManager* texture, SDL_Renderer* render);
	void focusCarpetPlace(int x, int y);
	void focusCarpetDir(int x, int y);//delete
	void focusDirArrows(int x, int y);
	short getCurrentPlayer();
	Field();
	~Field();
private:
	//Cells parameters
	int posX[9];
	int posY[9];
	int cellSize;

	//Asams parameters
	int asamPosX;
	int asamPosY;
	Direction asamDir;
	int asamSteps;

	//Focus (Action) parameters
	Direction focusDir;
	int selectPosX;
	int selectPosY;

	//Temporary parameters
	Direction chosenDir;
	int chosenX;
	int chosenY;
	short stage;
	char str1[11];

	//Draw positions
	short textPosX1;
	short textPosX2;



	//Game parameters
	short countPlayers;
	short currentPlayer;
	short step;
	short moneyPlayer[4];
	short carpetsPlayer[4];
	short diceValue;
	short paymentPoint;
	Carpet carpet[48];
	short currentNum;
	short cellsColor[49];
	bool cellsChecked[49];
	
};

