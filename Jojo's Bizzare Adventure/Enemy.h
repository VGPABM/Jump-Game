#pragma once
#include "stdafx.h"

class Enemy
{
private:
	unsigned pointCount;
	sf::Sprite circle;
	sf::Texture texture;
	sf::SoundBuffer buffer;
	sf::Sound roadroller;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initTexture();
	void initSound();
	void initVariables();
	void initShape();
public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;
	void stopMusic();

	void update();
	void render(sf::RenderTarget& target);
};

