#include "Obstacle.h"



void Obstacle::initShape()
{
	this->initTexture();
	float temp;
	temp = rand() % 3;
	std::cout << temp << std::endl;
	if (temp == 0) {
		this->type = KNIFE;
		this->damage = 10;
		this->shape.setTexture(knife);
		this->shape.setScale(0.8f, 0.8f);
		this->shape.setTextureRect(sf::IntRect(0, 80, 240, 80));
	}
	else if (temp == 1) {
		this->type = LOGO;
		this->damage = 20;
		this->german.setTexture(logo);
		this->german.setScale(0.8f, 0.8f);
		//this->german.setTextureRect(sf::IntRect(50, 50, 644, 325));
	}
	else if (temp == 2) {
		this->type = FIREBALL;
		this->damage = 15;
		this->circle.setTexture(fireball);
		this->circle.setTextureRect(sf::IntRect(100, 10, 622, 325));
		this->circle.setScale(0.4f, 0.4f);
	}
	else if (temp == 3) {

	}
	
}

void Obstacle::initVariables()
{
	this->speed = -5.f;
	this->hp = 10;
	this->hpMax = 0;
	this->damage= 10 ;
	this->point = 5;
}

void Obstacle::initTexture()
{
	knife.loadFromFile("Resources/Images/Sprite/Resource/obstacle_1.png");
	logo.loadFromFile("Resources/Images/Sprite/Resource/obstacle_2.png");
	fireball.loadFromFile("Resources/Images/Sprite/Resource/fireball.png");
}

Obstacle::Obstacle(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape();
	this->shape.setPosition(pos_x, pos_y);
	this->circle.setPosition(pos_x, pos_y);
	this->german.setPosition(pos_x, pos_y);
}

Obstacle::~Obstacle()
{

}

const sf::FloatRect Obstacle::getBoundsCircle() const {
	return this->circle.getGlobalBounds();	
}

const sf::FloatRect Obstacle::getBoundsSquare() const {
	return this->shape.getGlobalBounds();
}

const sf::FloatRect Obstacle::getBoundsGerman() const
{
	return this->german.getGlobalBounds();
}

const int& Obstacle::getDamage() const
{
	return this->damage;
}

void Obstacle::update()
{
	this->shape.move(this->speed,0.f);
	this->circle.move(this->speed, 0.f);
	this->german.move(this->speed, 0.f);
	this->german.setOrigin((sf::Vector2f)logo.getSize() / 2.f);
	this->german.rotate(10000000.f);
}

void Obstacle::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->circle);
	target.draw(this->german);
}
