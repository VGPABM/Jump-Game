#pragma once
#include "stdafx.h"
#include "Ellipse.h"

enum type{KNIFE=0,FIREBALL,LOGO};

class Obstacle
{
private:
	sf::Sprite shape;
	sf::Sprite german;
	sf::Sprite circle;
    EllipseShape ellips;
	sf::Texture knife;
	short type;
	sf::Texture logo;
	sf::Texture fireball;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int point;

	void initShape();
	void initVariables();
	void initTexture();
public:
	Obstacle(float pos_x, float pos_y);
	virtual ~Obstacle();

	const sf::FloatRect getBoundsCircle() const;
	const sf::FloatRect getBoundsSquare() const;
	const sf::FloatRect getBoundsGerman() const;
	const int& getDamage() const;

	void update();
	void render(sf::RenderTarget& target);
};



