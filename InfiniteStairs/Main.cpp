#include "Contents/InfiniteStairs.h"

#include <Windows.h>
#include <iostream>

int main()
{
	/*while (1)
	{
		std::cout << "wert\n";
		Sleep(10);
	}*/
	SetConsoleOutputCP(CP_UTF8);
	system("mode con cols=120 lines=50");
	InfiniteStairs game;
	game.Run();
}
