// Marrakesh.cpp: определяет точку входа для консольного приложения.
//
#ifdef _DEBUG
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#endif
#include "stdafx.h"
#include "GMain.h"
#include <ctime>


int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand((unsigned)time(NULL));
	GMain game;
	game.init();
	game.mainLoop();
    return 0;
}

