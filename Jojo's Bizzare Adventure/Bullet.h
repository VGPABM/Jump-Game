#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>

class Bullet
{
private:
	sf::RectangleShape shape;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f direction;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;
	float movementSpeed;
	

public:
	void initShape();
	void initTexture();
	Bullet(float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Bullet();
	void initVariables();
	void initSound();

	//Accessor
	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget& target);
	
};

