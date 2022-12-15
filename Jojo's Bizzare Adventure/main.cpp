#include"Game.h"


int main() 
{
	srand(static_cast<unsigned>(time(0)));

	Game main;
	while (main.getwindow().isOpen())
	{
		main.update();
		main.render();
	}

	return 0;
	
}