#pragma once
#include"stdafx.h"
#include"Player.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;

	Player* player;

	void initWindow();
	void initPlayer();

public:
	//Functions
	Game();
	virtual ~Game();

	void updateCollision();
	void updatePlayer();
	void update();
	void renderPlayer();
	void render();
	const sf::RenderWindow& getwindow();
	
};


