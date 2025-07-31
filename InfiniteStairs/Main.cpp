#include "Contents/InfiniteStairs.h"

#include <Windows.h>
#include <iostream>

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	system("mode con cols=50 lines=50");
	InfiniteStairs game;
	game.Run();
}
