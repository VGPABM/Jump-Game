#include"Game.h"
#include "Player.h"

int main() 
{
	srand(static_cast<unsigned>(time(0)));

	Game main;
	while (main.getwindow().isOpen())
	{
		main.run();
	}

	return 0;
	
}