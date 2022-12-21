#include "Bullet.h"

void Bullet::initShape()
{
	float height, width;
	height = 25;
	width = 30;
	this->shape.setSize(sf::Vector2f(width, height));
	shape.setTexture(&texture);
	shape.setTextureRect(sf::IntRect(10, 10, 100, 100));
	//this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
	/*this->initTexture();
	sprite.setTexture(texture);*/
	//sprite.getTextureRect(0, 0, 820, 166);
}

void Bullet::initTexture()
{
	if(!texture.loadFromFile("Resources/Images/Sprite/Resource/Bullet.png"))std::cout<<"Could not load";
}

Bullet::Bullet(float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
	this->initShape();
	std::cout << dir_x << std::endl;
	std::cout << dir_y << std::endl;
	this->aimDir.x = pos_x - dir_x;
	this->aimDir.y = pos_y - dir_y;
	this->aimDirNorm = sf::Vector2f(aimDir.x / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)), aimDir.y / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
	this->movementSpeed = movement_speed;
	this->shape.setPosition(pos_x, pos_y);
}

Bullet::~Bullet()
{

}

void Bullet::initVariables()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Bullet::update()
{
	//Movement Update

	this->shape.move((-1)*this->movementSpeed * this->aimDirNorm);
}

void Bullet::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
