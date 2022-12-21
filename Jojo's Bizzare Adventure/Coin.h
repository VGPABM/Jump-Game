#pragma once
#include "stdafx.h"

class Coin
{
private:
	unsigned pointCount;
	sf::Sprite coinSprite;
	sf::Texture coinTexture;
	sf::CircleShape circle;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initVariables();
	void initShape();
	void initTexture();
public:
	Coin(float pos_x, float pos_y);
	virtual ~Coin();

	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	void update();
	void render(sf::RenderTarget& target);
};

