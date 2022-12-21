#include "Coin.h"

void Coin::initVariables()
{
	this->pointCount = 1; //minimum 0 max 10
	this->type = 0;
	this->speed = -5.f;
	this->hp = static_cast<float>(this->pointCount);;
	this->points = 1;
}

void Coin::initShape()
{
	this->initTexture();
	this->circle.setRadius(50);
	this->circle.setPointCount(100);
	//this->circle.setFillColor(sf::Color(150, 50, 250, 255));
	this->circle.setTexture(&coinTexture);
}

void Coin::initTexture()
{
	coinTexture.loadFromFile("Resources/Images/Sprite/Resource/Jojo_coin.png");
}

Coin::Coin(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape();
	this->circle.setPosition(pos_x, pos_y);
}

Coin::~Coin()
{

}

const sf::FloatRect Coin::getBounds() const {
	return this->circle.getGlobalBounds();
}

const int& Coin::getPoints() const
{
	return this->points;
}

const int& Coin::getDamage() const
{
	return this->damage;
}

void Coin::update()
{
	this->circle.move(this->speed, 0.f);
}

void Coin::render(sf::RenderTarget& target)
{
	target.draw(this->circle);
}
