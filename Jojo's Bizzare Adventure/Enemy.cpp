#include "Enemy.h"

void Enemy::initTexture()
{
	texture.loadFromFile("Resources/Images/Sprite/Resource/Enemy.png");
}

void Enemy::initSound()
{
	buffer.loadFromFile("Resources/sound/roadroller.ogg");
	roadroller.setBuffer(buffer);
	roadroller.setVolume(30.f);
}

void Enemy::initVariables()
{
	this->pointCount = 1; //minimum 0 max 10
	this->type = 0;
	this->speed = -5.f;
	this->hp = static_cast<float>(this->pointCount);;
	this->hpMax = this->hpMax;
	this->damage = 20;
	this->points = this->pointCount;
}

void Enemy::initShape()
{
	this->initTexture();
	this->circle.setTexture(texture);
	this->circle.setScale(0.5f, 0.5f);
	this->circle.setTextureRect(sf::IntRect(50, 50, 644, 325));
}

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();
	this->initSound();
	this->initShape();
	this->circle.setPosition(pos_x, pos_y);
	roadroller.play();
}

Enemy::~Enemy()
{

}

const sf::FloatRect Enemy::getBounds() const {
	return this->circle.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

void Enemy::stopMusic()
{
	this->roadroller.stop();
}

void Enemy::update()
{
	this->circle.move(this->speed, 0.f);
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->circle);
}
