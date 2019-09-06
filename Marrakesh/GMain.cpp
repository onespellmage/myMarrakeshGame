#include "stdafx.h"
#include "GMain.h"


GMain::GMain()
{
	for (int i = 0; i < 49; i++)
		mass[i] = 0;
	posChar = 25;
	quit = false;
	Lock = false;
	state = menu;
	csdl_setup = new CSDL_Setup(&quit);
	Texture = new TextureManager();
	playerNum = 2;
	//ТЕСТ(удалить)
	angle=0.0;
	steps = AsamDir;
	currentPl = 0;
	xSize = 24;
	ySize = 30;
	hasteX = 1;
	hasteY = 1;
	speedX = 1;
	speedY = 1;
}


GMain::~GMain()
{
	delete csdl_setup;
	delete Texture;
}

void GMain::init()
{
	Texture->load("images/MarrakechMain.jpg", "MainMenu", csdl_setup->GetRenderer());

	Texture->load("images/MBoard.png", "MBoard", csdl_setup->GetRenderer());
	Texture->load("images/grad.png", "mor", csdl_setup->GetRenderer());
	Texture->load("images/Carpet1.png", "1", csdl_setup->GetRenderer());
	Texture->load("images/Carpet2.png", "2", csdl_setup->GetRenderer());
	Texture->load("images/Carpet3.png", "3", csdl_setup->GetRenderer());
	Texture->load("images/Carpet4.png", "4", csdl_setup->GetRenderer());
	Texture->load("images/arrow1.png", "Arrow", csdl_setup->GetRenderer());
	Texture->load("images/Asam2.png", "Asam", csdl_setup->GetRenderer());
	Texture->load("images/ButtonAccept.png", "ButtonAccept", csdl_setup->GetRenderer());
	Texture->load("images/Dice.png", "Dice", csdl_setup->GetRenderer());
	Texture->load("images/Cell.png", "Cell", csdl_setup->GetRenderer());
	//Texture->load("images/Info4.png", "Info", csdl_setup->GetRenderer());
	Texture->WriteText("But1", csdl_setup->GetRenderer(), "Start", 40, 255, 255, 255);
	Texture->WriteText("NPlayer", csdl_setup->GetRenderer(), "Players: 2", 36, 255, 255, 255);
	Texture->WriteText("But2", csdl_setup->GetRenderer(), "Exit", 40, 255, 255, 255);
	Texture->WriteText("Marker", csdl_setup->GetRenderer(), ">", 40, 255, 255, 255);
	Texture->WriteText("ButAccept", csdl_setup->GetRenderer(), "Accept", 24, 255, 255, 255);
	Texture->WriteText("Current", csdl_setup->GetRenderer(), "Current player: 1", 40, 255, 255, 255);
}

void GMain::draw()
{
	if (deltaX < 300)
	{
		speedX += hasteX;
		speedY += hasteY;
		deltaX += speedX;
		deltaY += speedY;
	}
	switch (state)
	{
	case menu:
		Texture->draw("MainMenu", 0, 0, 800, 600, csdl_setup->GetRenderer());
		Texture->DrawText("But1", csdl_setup->GetRenderer(), 360, 200);
		Texture->DrawText("NPlayer", csdl_setup->GetRenderer(), 330, 240);
		Texture->DrawText("But2", csdl_setup->GetRenderer(), 370, 280);
		Texture->DrawText("Marker", csdl_setup->GetRenderer(),10 + deltaX, 10 + deltaY);
		switch (focusButton)
		{
		case START:
			Texture->DrawText("Marker", csdl_setup->GetRenderer(), 340, 200);
			break;
		case PLAYER:
			Texture->DrawText("Marker", csdl_setup->GetRenderer(), 310, 240);
			break;
		case EXIT:
			Texture->DrawText("Marker", csdl_setup->GetRenderer(), 350, 280);
			break;
		case NONE:
			break;
		default:
			break;
		}
		break;
	case processS:
		Texture->draw("MBoard", 0, 0, 800, 600, csdl_setup->GetRenderer());
		field.drawField(Texture, csdl_setup->GetRenderer());
		Texture->draw("ButtonAccept", 635, 500, 140, 60, csdl_setup->GetRenderer());
		Texture->DrawText("ButAccept", csdl_setup->GetRenderer(), 640, 505);
		switch (steps)
		{
		case AsamDir:
			field.drawDirArrows(Texture, csdl_setup->GetRenderer());
			break;
		case DropDice:
			if (field.dropDice() == true)
				steps = AsamMove;
			break;
		case AsamMove:
			if (field.moveAsam() == true)
				steps = Payment;
			break;
		case Payment:
			field.payment();
			field.loadGametext(Texture, csdl_setup->GetRenderer());
			steps = SetCarpet;
			break;
		case SetCarpet:
			field.drawCarpetDir(Texture, csdl_setup->GetRenderer());
			break;
		default:
			break;
		}
		break;
	case score:
		break;
	}
	if (currentPl != field.getCurrentPlayer())
	{
		currentPl = field.getCurrentPlayer();
		if (currentPl==1)
			Texture->WriteText("Current", csdl_setup->GetRenderer(), "Current player: 1", 40, 255, 255, 255);
		else if (currentPl == 2)
			Texture->WriteText("Current", csdl_setup->GetRenderer(), "Current player: 2", 40, 255, 255, 255);
		else if(currentPl == 3)
			Texture->WriteText("Current", csdl_setup->GetRenderer(), "Current player: 3", 40, 255, 255, 255);
		else if(currentPl == 4)
			Texture->WriteText("Current", csdl_setup->GetRenderer(), "Current player: 4", 40, 255, 255, 255);
		else Texture->WriteText("Current", csdl_setup->GetRenderer(), "Current player: unknown", 40, 255, 255, 255);
	}
	Texture->DrawText("Current", csdl_setup->GetRenderer(),350, 0);
}

void GMain::mainLoop()
{
	while ((!quit) && (csdl_setup->GetMainEvent()->type != SDL_QUIT))
	{
		starting_tick = SDL_GetTicks();
		csdl_setup->Begin();
		SDL_GetMouseState(&MouseX, &MouseY);
		onFocus(MouseX, MouseY);
		draw();
		mouseAction();
		Texture->drawScale("mor", 0, 0,800,600, xSize, ySize, csdl_setup->GetRenderer());
		switch (csdl_setup->GetMainEvent()->type)
		{
		case SDL_KEYDOWN:
			switch (csdl_setup->GetMainEvent()->key.keysym.sym)
			{
			case SDLK_a:
				angle -= 60;
				break;
			case SDLK_s:
				if (xSize > 0)
				{
					xSize -= 6;
					ySize -= 6;
				}
				break;
			case SDLK_w:
				if (ySize < 60)
				{
					xSize += 6;
					ySize += 6;
				}
				break;
			}
			break;

		case SDL_QUIT:
			quit = true;
			break;
		default:
			break;
		}
		drawMessage();
		if ((1000 / fps) > SDL_GetTicks() - starting_tick)
		{
			SDL_Delay(1000 / fps - (SDL_GetTicks() - starting_tick));
		}
		csdl_setup->End();
	}
}

void GMain::mouseAction()
{
	if (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN)
	{
		if ((csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT) && (Lock == true))
		{
			Lock = false;
			switch (focusButton)
			{
			case START:
				state = processS;
				str = "images/Info" + std::to_string(playerNum) + ".png";
				Texture->load(str, "Info", csdl_setup->GetRenderer());
				field.setCountPlayer(playerNum);
				field.setNewGameParam();
				field.loadGametext(Texture, csdl_setup->GetRenderer());
				break;
			case PLAYER:
				if (playerNum < 4)
					playerNum++;
				else
					playerNum = 2;
				char str1[11];
				sprintf(str1, "Players: %d", playerNum);
				Texture->WriteText("NPlayer", csdl_setup->GetRenderer(), str1, 36, 255, 255, 255);
				break;
			case EXIT:
				quit = true;
				break;
			case FIELD:
				field.ClickAction(steps);
				break;
			case ACCEPT:
				if (field.Accept(steps) == true)
					if (steps == AsamDir)
						steps = DropDice;
					else if (steps == SetCarpet)
					{
						steps = AsamDir;
						field.loadGametext(Texture, csdl_setup->GetRenderer());
					}
				break;
			case NONE:
				break;
			default:
				break;
			}
		}
		if (csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_RIGHT)
		{
			switch (steps)
			{
			case AsamDir:
				field.CancelDir();
				break;
			case SetCarpet:
				field.CancelCarpet();
				break;
			default:
				break;
			}
		}
	}
	if (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONUP)
	{
		if ((csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT) && (Lock == false))
		{
			Lock = true;

		}
	}
}

void GMain::process()
{
	switch (state)
	{
	case menu:
		break;
	case processS:
		break;
	case score:
		break;
	}
}

void GMain::onFocus(int x, int y)
{
	if (state == menu)
	{
		if ((y >= 200) && (y <= 235) && (x >= 360) && (x <= 440))
		{
			focusButton = START;
			return;
		}
		if ((y >= 245) && (y <= 270) && (x >= 280) && (x <= 545))
		{
			focusButton = PLAYER;
			return;
		}
		if ((y >= 280) && (y <= 320) && (x >= 370) && (x <= 435))
		{
			focusButton = EXIT;
			return;
		}
	}
	if (state == processS)
	{
		if ((y >= 500) && (y <= 560) && (x >= 635) && (x <= 775))
		{
			focusButton = ACCEPT;
			return;
		}
		if ((y >= 10) && (y <= 588) && (x >= 27) && (x <= 604))
		{
			focusButton = FIELD;
			switch (steps)
			{
			case AsamDir:
				field.focusDirArrows(x, y);
				return;
				break;
			case SetCarpet:
				field.focusCarpetPlace(x, y);
				return;
				break;
			}
		}
	}
	focusButton = NONE;
}

void GMain::drawMessage()
{


}
