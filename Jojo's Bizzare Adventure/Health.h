#pragma once
#include "stdafx.h"

class Health
{
private:
	unsigned pointCount;
	sf::Texture texture;
	sf::Sprite circle;
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
	Health(float pos_x, float pos_y);
	virtual ~Health();

	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getDamage() const;

	void update();
	void render(sf::RenderTarget& target);
};
