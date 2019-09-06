#include "stdafx.h"
#include "Field.h"

Field::Field()
{
	posX[0] = 35;
	posX[1] = 98;
	posX[2] = 160;
	posX[3] = 223;
	posX[4] = 286;
	posX[5] = 348;
	posX[6] = 411;
	posX[7] = 474;
	posX[8] = 536;
	posY[0] = 20;
	posY[1] = 83;
	posY[2] = 145;
	posY[3] = 208;
	posY[4] = 271;
	posY[5] = 333;
	posY[6] = 396;
	posY[7] = 458;
	posY[8] = 521;
	cellSize = 60;
}


Field::~Field()
{
}


void Field::setNewGameParam()
{
	asamPosX = 4;
	asamPosY = 4;
	asamDir = South;
	for (int i = 0; i < 4; i++)
		moneyPlayer[i] = 30;
	switch (countPlayers)
	{
	case 2:
		carpetsPlayer[0] = 12;
		carpetsPlayer[1] = 12;
		carpetsPlayer[2] = 12;
		carpetsPlayer[3] = 12;
		break;
	case 3:
		carpetsPlayer[0] = 15;
		carpetsPlayer[1] = 15;
		carpetsPlayer[2] = 15;
		break;
	case 4:
		carpetsPlayer[0] = 12;
		carpetsPlayer[1] = 12;
		carpetsPlayer[2] = 12;
		carpetsPlayer[3] = 12;
		break;
	}
	for (int i = 0; i < 49; i++)
		cellsColor[i] = 0;
	currentNum = 0;
	diceValue = 1;
	step = 0;
	currentPlayer = 1;
	chosenDir = None;
	focusDir = None;
	selectPosX = 0;
	selectPosY = 0;
	stage = 0;
	paymentPoint = 0;
	for (int i = 0; i < 49; i++)
	{
		cellsChecked[i] = false;
	}
	
}

void Field::setSelectPos()
{
	switch (focusDir)
	{
	case North:
		selectPosX = asamPosX - 1;
		selectPosY = asamPosY;
		break;

	case West:
		selectPosX = asamPosX;
		selectPosY = asamPosY-1;
		break;

	case East:
		selectPosX = asamPosX;
		selectPosY = asamPosY+1;
		break;

	case South:
		selectPosX = asamPosX + 1;
		selectPosY = asamPosY;
		break;
	case None:
		selectPosX = 0;
		selectPosY = 0;
		break;
	}
}

void Field::setCountPlayer(int count)
{
	countPlayers = count;
}


void Field::drawCarpetDir(TextureManager * texture, SDL_Renderer * render)
{
	if (step == 0)
	{
		if (asamPosY > 1)
			texture->draw("Cell", posX[asamPosX], posY[asamPosY - 1], cellSize, cellSize, render);
		if (asamPosX < 7)
			texture->draw("Cell", posX[asamPosX + 1], posY[asamPosY], cellSize, cellSize, render);
		if (asamPosX > 1)
			texture->draw("Cell", posX[asamPosX - 1], posY[asamPosY], cellSize, cellSize, render);
		if (asamPosY < 7)
			texture->draw("Cell", posX[asamPosX], posY[asamPosY + 1], cellSize, cellSize, render);
	}
	else if(step==1)
	{
		if (focusDir != None)
			texture->drawVertical(std::to_string(currentPlayer), posX[selectPosX], posY[selectPosY], 120, 60, render, focusDir*90.0);
	}
	else if (step == 2)
	{
		texture->drawVertical(std::to_string(currentPlayer), posX[carpet[currentNum].posX], posY[carpet[currentNum].posY], 120, 60, render, carpet[currentNum].carpetDir*90.0);
	}
}

void Field::drawDirArrows(TextureManager * texture, SDL_Renderer* render)
{
	switch (asamDir)
	{
	case North:
		texture->drawWithRotate("Arrow", posX[asamPosX], posY[asamPosY-1], cellSize, cellSize, render, North*90.0, SDL_FLIP_NONE);
		texture->drawWithRotate("Arrow", posX[asamPosX-1], posY[asamPosY], cellSize, cellSize, render, West*90.0, SDL_FLIP_NONE);
		texture->drawWithRotate("Arrow", posX[asamPosX+1], posY[asamPosY], cellSize, cellSize, render, East*90.0, SDL_FLIP_NONE);
		break;

	case West:
		texture->drawWithRotate("Arrow", posX[asamPosX], posY[asamPosY - 1], cellSize, cellSize, render, North*90.0, SDL_FLIP_NONE);
		texture->drawWithRotate("Arrow", posX[asamPosX - 1], posY[asamPosY], cellSize, cellSize, render, West*90.0, SDL_FLIP_NONE);
		texture->drawWithRotate("Arrow", posX[asamPosX], posY[asamPosY + 1], cellSize, cellSize, render, South*90.0, SDL_FLIP_NONE);
		break;

	case East:
		texture->drawWithRotate("Arrow", posX[asamPosX], posY[asamPosY - 1], cellSize, cellSize, render, North*90.0, SDL_FLIP_NONE);
		texture->drawWithRotate("Arrow", posX[asamPosX + 1], posY[asamPosY], cellSize, cellSize, render, East*90.0, SDL_FLIP_NONE);
		texture->drawWithRotate("Arrow", posX[asamPosX], posY[asamPosY + 1], cellSize, cellSize, render, South*90.0, SDL_FLIP_NONE);
		break;

	case South:
		texture->drawWithRotate("Arrow", posX[asamPosX], posY[asamPosY + 1], cellSize, cellSize, render, South*90.0, SDL_FLIP_NONE);
		texture->drawWithRotate("Arrow", posX[asamPosX - 1], posY[asamPosY], cellSize, cellSize, render, West*90.0, SDL_FLIP_NONE);
		texture->drawWithRotate("Arrow", posX[asamPosX + 1], posY[asamPosY], cellSize, cellSize, render, East*90.0, SDL_FLIP_NONE);
		break;
	}
}

void Field::drawField(TextureManager * texture, SDL_Renderer * render)
{
	for (short i = 0; i < currentNum; i++)
		texture->drawVertical(std::to_string(carpet[i].player), posX[carpet[i].posX], posY[carpet[i].posY], 120, 60, render, carpet[i].carpetDir*90.0);
	texture->drawWithRotate("Asam", posX[asamPosX], posY[asamPosY], cellSize, cellSize, render, asamDir*90.0, SDL_FLIP_NONE);
	texture->draw("Info", 636, 30, 148, 240, render);
	texture->drawFrame("Dice", 675, 355, 60, 60,1,diceValue-1, render);
	switch (countPlayers)
	{
	case 2:
		texture->DrawText("Gold1", render, 630, 90);
		texture->DrawText("Carpet1", render, 690, 68);
		texture->DrawText("Carpet3", render, 690, 115);
		texture->DrawText("Gold2", render, 630, 205);
		texture->DrawText("Carpet2", render, 690, 182);
		texture->DrawText("Carpet4", render, 690, 225);
		break;
	case 3:
		texture->DrawText("Gold1", render, 636, 65);
		texture->DrawText("Carpet1", render, 695, 65);
		texture->DrawText("Gold2", render, 636, 146);
		texture->DrawText("Carpet2", render, 695, 146);
		texture->DrawText("Gold3", render, 636, 228);
		texture->DrawText("Carpet3", render, 695, 228);
		break;
	case 4:
		texture->DrawText("Gold1", render, 636, 65);
		texture->DrawText("Carpet1", render, 695, 65);
		texture->DrawText("Gold2", render, 636, 125);
		texture->DrawText("Carpet2", render, 695, 125);
		texture->DrawText("Gold3", render, 636, 185);
		texture->DrawText("Carpet3", render, 695, 185);
		texture->DrawText("Gold4", render, 636, 245);
		texture->DrawText("Carpet4", render, 695, 245);
		break;
	}

}

void Field::loadGametext(TextureManager * texture, SDL_Renderer * render)
{

	switch (countPlayers)
	{
	case 2:
		sprintf(str1, "%d", moneyPlayer[0]);
		texture->WriteText("Gold1", render,str1, 20, 0, 0, 0);
		sprintf(str1, "%d", carpetsPlayer[0]);
		texture->WriteText("Carpet1", render, str1, 20, 0, 0, 0);
		sprintf(str1, "%d", carpetsPlayer[2]);
		texture->WriteText("Carpet3", render, str1, 20, 0, 0, 0);
		sprintf(str1, "%d", moneyPlayer[1]);
		texture->WriteText("Gold2", render, str1, 20, 0, 0, 0);
		sprintf(str1, "%d", carpetsPlayer[1]);
		texture->WriteText("Carpet2", render, str1, 20, 0, 0, 0);
		sprintf(str1, "%d", carpetsPlayer[3]);
		texture->WriteText("Carpet4", render, str1, 20, 0, 0, 0);
		break;
	case 3:
		sprintf(str1, "%d", moneyPlayer[0]);
		texture->WriteText("Gold1", render, str1, 20, 0, 0, 0);
		sprintf(str1, "%d", carpetsPlayer[0]);
		texture->WriteText("Carpet1", render, str1, 20, 0, 0, 0);
		sprintf(str1, "%d", moneyPlayer[1]);
		texture->WriteText("Gold2", render, str1, 20, 0, 0, 0);
		sprintf(str1, "%d", carpetsPlayer[1]);
		texture->WriteText("Carpet2", render, str1, 20, 0, 0, 0);
		sprintf(str1, "%d", moneyPlayer[2]);
		texture->WriteText("Gold3", render, str1, 20, 0, 0, 0);
		sprintf(str1, "%d", carpetsPlayer[2]);
		texture->WriteText("Carpet3", render, str1, 20, 0, 0, 0);
		break;
	case 4:
		sprintf(str1, "%d", moneyPlayer[0]);
		texture->WriteText("Gold1", render, str1, 20, 0, 0, 0);
		sprintf(str1, "%d", carpetsPlayer[0]);
		texture->WriteText("Carpet1", render, str1, 20, 0, 0, 0);
		sprintf(str1, "%d", moneyPlayer[1]);
		texture->WriteText("Gold2", render, str1, 20, 0, 0, 0);
		sprintf(str1, "%d", carpetsPlayer[1]);
		texture->WriteText("Carpet2", render, str1, 20, 0, 0, 0);
		sprintf(str1, "%d", moneyPlayer[2]);
		texture->WriteText("Gold3", render, str1, 20, 0, 0, 0);
		sprintf(str1, "%d", carpetsPlayer[2]);
		texture->WriteText("Carpet3", render, str1, 20, 0, 0, 0);
		sprintf(str1, "%d", moneyPlayer[3]);
		texture->WriteText("Gold4", render, str1, 20, 0, 0, 0);
		sprintf(str1, "%d", carpetsPlayer[3]);
		texture->WriteText("Carpet4", render, str1, 20, 0, 0, 0);
		break;
	}
}

void Field::focusCarpetPlace(int x, int y)
{
	if (step == 0)
	{
		if ((y >= posY[asamPosY]) && (y <= posY[asamPosY] + cellSize))
		{
			//East
			if ((asamPosX < 7) && (x >= posX[asamPosX + 1]) && (x <= posX[asamPosX + 1] + cellSize))
			{
				focusDir = East;
				return;
			}
			//West
			if ((asamPosX > 1) && (x >= posX[asamPosX - 1]) && (x <= posX[asamPosX - 1] + cellSize))
			{
				focusDir = West;
				return;
			}
		}
		if ((x >= posX[asamPosX]) && (x <= posX[asamPosX] + cellSize))
		{
			//South
			if ((asamPosY < 7) && (y >= posY[asamPosY + 1]) && (y <= posY[asamPosY + 1] + cellSize))
			{
				focusDir = South;
				return;
			}
			//North
			if ((asamPosY > 1) && (y >= posY[asamPosY - 1]) && (y <= posY[asamPosY - 1] + cellSize))
			{
				focusDir = North;
				return;
			}
		}
	}
	else if(step==1)
	{
		if ((y >= posY[selectPosY]) && (y <= posY[selectPosY] + cellSize))
		{
			//East
			if ((selectPosX<7) && (asamPosX != selectPosX + 1) && (x >= posX[selectPosX + 1]) && (x <= posX[selectPosX + 1] + cellSize))
			{
				focusDir = East;

				return;
			}
			//West
			if ((selectPosX>1) && (asamPosX != selectPosX - 1) && (x >= posX[selectPosX - 1]) && (x <= posX[selectPosX - 1] + cellSize))
			{
				focusDir = West;
				return;
			}
		}
		if ((x >= posX[selectPosX]) && (x <= posX[selectPosX] + cellSize))
		{
			//South
			if ((selectPosY<7)&& (asamPosY!= selectPosY + 1) && (y >= posY[selectPosY + 1]) && (y <= posY[selectPosY + 1] + cellSize))
			{
				focusDir = South;
				return;
			}
			//North
			if ((selectPosY>1) && (asamPosY != selectPosY - 1) && (y >= posY[selectPosY - 1]) && (y <= posY[selectPosY - 1] + cellSize))
			{
				focusDir = North;
				return;
			}
		}
	}
	focusDir = None;
}

void Field::focusCarpetDir(int x, int y)
{
	
	focusDir = None;
}

void Field::focusDirArrows(int x, int y)
{
	if ((y >= posY[asamPosY]) && (y <= posY[asamPosY] + cellSize))
	{
		//East
		if ((asamDir != West) && (x >= posX[asamPosX+1]) && (x <= posX[asamPosX+1] + cellSize))
		{
			focusDir = East;
			return;
		}
		//West
		if ((asamDir!=East)&&(x >= posX[asamPosX-1]) && (x <= posX[asamPosX-1] + cellSize))
		{
			focusDir = West;
			return;
		}
	}
	if ((x >= posX[asamPosX]) && (x <= posX[asamPosX] + cellSize))
	{
		//South
		if ((asamDir != North) && (y >= posY[asamPosY + 1]) && (y <= posY[asamPosY + 1] + cellSize))
		{
			focusDir = South;
			return;
		}
		//North
		if ((asamDir != South) && (y >= posY[asamPosY - 1]) && (y <= posY[asamPosY - 1] + cellSize))
		{
			focusDir = North;
			return;
		}
	}
	focusDir = None;
}

short Field::getCurrentPlayer()
{
	return currentPlayer;
}

Direction Field::getFocusDir()
{
	return focusDir;
}

void Field::ClickAction(short act)
{
	switch(act)
	{
		case 1:
			chosenDir = focusDir;
			break;
		case 5:
			if (step == 0)
			{
				step = 1;
				switch (focusDir)
				{
				case North:
					selectPosX = asamPosX;
					selectPosY = asamPosY - 1;
					break;

				case West:
					selectPosX = asamPosX - 1;
					selectPosY = asamPosY;
					break;

				case East:
					selectPosX = asamPosX + 1;
					selectPosY = asamPosY;
					break;

				case South:
					selectPosX = asamPosX;
					selectPosY = asamPosY + 1;
					break;

				}
			}
			else if (step==1)
			{
				carpet[currentNum].posX= selectPosX;
				carpet[currentNum].posY= selectPosY;
				carpet[currentNum].carpetDir = focusDir;
				carpet[currentNum].player = currentPlayer;
				step = 2;
			}
			break;
		default:
			break;
	}
}

bool Field::Accept(short stepss)
{
	if ((stepss == 1)&& (chosenDir!=None))
	{
		asamDir = chosenDir;
		chosenDir = None;
		return true;
	}
	if (stepss == 5)
	{
		cellsColor[(selectPosX-1+(selectPosY-1)*7)] = currentPlayer;
		switch (carpet[currentNum].carpetDir)
		{
		case North:
			cellsColor[(selectPosX-1 + (selectPosY-1-1) * 7)] = currentPlayer;
			break;

		case West:
			cellsColor[(selectPosX-1-1 + (selectPosY-1) * 7)] = currentPlayer;
			break;

		case East:
			cellsColor[(selectPosX-1 + 1 + (selectPosY - 1) * 7)] = currentPlayer;
			break;

		case South:
			cellsColor[(selectPosX-1 + (selectPosY -1+ 1) * 7)] = currentPlayer;
			break;
		}
		carpetsPlayer[currentPlayer - 1]--;
		currentNum++;
		step = 0;
		if (currentPlayer < 4)
			currentPlayer++;
		else
			currentPlayer = 1;
		return true;
	}
	return false;
}

void Field::CancelDir()
{	
	chosenDir = None;
}

void Field::CancelCarpet()
{
	step = 0;
}

bool Field::dropDice()
{
	stage++;
	if ((stage == 10) || (stage == 20) || (stage == 30) || (stage == 45) || (stage == 60) || (stage == 90) || (stage == 120))
	{
		diceValue = 1 + rand() % 6;
		if (diceValue == 3)
			diceValue = 2;
		else if ((diceValue == 4)|| (diceValue == 5))
			diceValue = 3;
		else if (diceValue == 6)
			diceValue = 4;
	}
	if (stage >= 121)
	{
		stage = 0;
		asamSteps = diceValue;
		return true;
	}
	return false;
}

bool Field::moveAsam()
{
	stage++;
	if (stage % 30 == 0)
	{
		if (asamSteps == 0)
		{
			stage = 0;
			return true;
		}
		else
			asamSteps--;
		switch (asamDir)
		{
		case North:
			if (asamPosY < 2)
			{
				if (asamPosX == 1)
					asamDir = East;
				else if (asamPosX % 2 == 0)
				{
					asamPosX++;
					asamDir = South;
				}
				else
				{
					asamPosX--;
					asamDir = South;
				}
			}
			else
				asamPosY--;
			break;

		case West:
			if (asamPosX < 2)
			{
				if (asamPosY == 1)
					asamDir = South;
				else if (asamPosY % 2 == 0)
				{
					asamPosY++;
					asamDir = East;
				}
				else
				{
					asamPosY--;
					asamDir = East;
				}
			}
			else
				asamPosX--;
			break;

		case East:
			if (asamPosX > 6)
			{
				if (asamPosY == 7)
					asamDir = South;
				else if (asamPosY % 2 == 0)
				{
					asamPosY--;
					asamDir = West;
				}
				else
				{
					asamPosY++;
					asamDir = West;
				}
			}
			else
				asamPosX++;
			break;

		case South:
			if (asamPosY > 6)
			{
				if (asamPosX == 7)
					asamDir = West;
				else if (asamPosX % 2 == 0)
				{
					asamPosX--;
					asamDir = North;
				}
				else
				{
					asamPosX++;
					asamDir = North;
				}
			}
			else
				asamPosY++;
			break;
		}
	}
	return false;
}

void Field::payment()
{
	int asamPosColor = asamPosX-1+(asamPosY-1)*7;
	if ((currentPlayer == cellsColor[asamPosColor]) || (cellsColor[asamPosColor] == 0))
		return;
	paymentPoint = 1;
	cellsChecked[asamPosColor] = true;
	countPayment(asamPosColor, cellsColor[asamPosColor]);
	for (int i = 0; i < 49; i++)
	{
		cellsChecked[i] = false;
	}
	moneyPlayer[currentPlayer-1] -= paymentPoint;
	moneyPlayer[cellsColor[asamPosColor]-1] += paymentPoint;
	paymentPoint = 0;
}

void Field::countPayment( int current, int color)
{
	
	if ((current - 7 >= 0) && (!cellsChecked[current - 7]) && (cellsColor[current - 7] == color))
	{
		paymentPoint += 1;
		cellsChecked[current - 7] = true;
		countPayment( current - 7, color);
		std::cout << "OK! " << current - 7 << " from " << current << std::endl;
	}
	if ((current + 1 <= 48) && (!cellsChecked[current+1]) && ((current + 1) % 7 != 0) && (cellsColor[current + 1] == color))
	{
		paymentPoint += 1;
		cellsChecked[current +1] = true;
		countPayment( current + 1, color);
		std::cout << "OK! " << current + 1 << " from " << current << std::endl;
	}
	if ((current + 7 <= 48) && (!cellsChecked[current + 7]) && (cellsColor[current + 7] == color))
	{
		paymentPoint += 1;
		cellsChecked[current + 7] = true;
		countPayment(current + 7, color);
		std::cout << "OK! " << current + 7 << " from " << current << std::endl;
	}
	if ((current - 1 >= 0) && (!cellsChecked[current - 1]) && ((current) % 7 != 0) && (cellsColor[current - 1] == color))
	{
		paymentPoint += 1;
		cellsChecked[current -1] = true;
		countPayment(current - 1, color);
		std::cout << "OK! " << current - 1 << " from " << current << std::endl;
	}
}



