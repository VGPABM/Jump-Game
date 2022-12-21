#include "Health.h"

void Health::initVariables()
{
	this->pointCount = 1; //minimum 0 max 10
	this->type = 0;
	this->speed = -5.f;
	this->hp = 35;
	this->points = 1;
}

void Health::initShape()
{
	this->initTexture();
	this->circle.setTexture(texture);
	this->circle.setScale(0.4f, 0.4f);
	//this->circle.setFillColor(sf::Color(150, 50, 250, 255));
}

void Health::initTexture()
{
	texture.loadFromFile("Resources/Images/Sprite/Resource/heart.png");
}

Health::Health(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape();
	this->circle.setPosition(pos_x, pos_y);
}

Health::~Health()
{

}

const sf::FloatRect Health::getBounds() const {
	return this->circle.getGlobalBounds();
}

const int& Health::getHp() const
{
	return this->hp;
}

const int& Health::getDamage() const
{
	return this->damage;
}

void Health::update()
{
	this->circle.move(this->speed, 0.f);
}

void Health::render(sf::RenderTarget& target)
{
	target.draw(this->circle);
}

