#include "Player.h"

void Player::initVariables()
{
	this->animState = IDLE;
	this->lastPressedkey = RIGHT;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Resources/Images/Sprite/Player/jojo_combined.png")) 
	{
		std::cout << "ERROR::PLAYER::COULD not load player sheet!" << std::endl;
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 146, 212);

	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(0.75f, 0.75f);
}

void Player::initAnimation()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}


Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimation();
	this->initPhysics();
}

Player::~Player()
{

}

void Player::updateMovement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //LEFT
	{
		this->move(-1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATE::MOVING_LEFT;
		this->lastPressedkey = LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Right
	{
		this->move(1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATE::MOVING_RIGHT;
		this->lastPressedkey = RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //JUMP
	{
		this->move(0.f, -1.f);
		this->animState = PLAYER_ANIMATION_STATE::JUMPING;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //crouch
	{
		this->move(0.f, 1.f);
		
	}
	else if (this->lastPressedkey == RIGHT)
	{
		this->animState = PLAYER_ANIMATION_STATE::IDLE;
	}
	else if (this->lastPressedkey == LEFT) {
		this->animState = PLAYER_ANIMATION_STATE::IDLE_LEFT;
	}
}

void Player::initPhysics()
{
	this->maxVelocity = 2.3f;
	this->minVelocity = 1.f;
	this->acceleration = 2.f;
	this->accelerationY = 2.f;
	this->drag = 0.94f;
	this->gravity = 0.38f;
	this->maxVelocityY = 2.3f;
	this->maxVelocityFallingY = 9.0f;
}

void Player::updateAnimation()
{
	if (this->animState == PLAYER_ANIMATION_STATE::IDLE || this->animState == PLAYER_ANIMATION_STATE::IDLE_LEFT) {

		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.35f || this->getAnimSwitch()) {

			this->currentFrame.top = 0.f;
			this->currentFrame.left += 146.f;
			if (this->currentFrame.left >= 730.f)
			{
				this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATE::MOVING_RIGHT) 
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.14f || this->getAnimSwitch()) {

			this->currentFrame.top = 212.f;
			this->currentFrame.left += 146.f;
			if (this->currentFrame.left >= 1168.f)
			{
				this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATE::MOVING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.14f || this->getAnimSwitch()) {

			this->currentFrame.top = 424.f;
			this->currentFrame.left += 146.f;
			if (this->currentFrame.left >= 1168.f)
			{
				this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}

	else if (this->animState == PLAYER_ANIMATION_STATE::JUMPING)
	{
		this->isAirborne = true;
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.14f || this->getAnimSwitch()) {

			this->currentFrame.top = 636.f;
			this->currentFrame.left += 146.f;
			if (this->currentFrame.left >= 1168.f)
			{
				this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}

}

void Player::update()
{
	this->updateMovement();
	this->updateAnimation();
	this->updatePhysics();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void Player::updatePhysics()
{
	//Gravity
	this->velocity.y += 3 * this->gravity;
	if (std::abs(this->velocity.y) > this->maxVelocityFallingY)
	{
		this->velocity.y = this->maxVelocityFallingY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}

	//Deceleration
	this->velocity *= this->drag;

	//Limit Deceleration
	if (std::abs(this->velocity.x) < this->minVelocity)
	{
		this->velocity.x = 0.f;
	} 
	if (std::abs(this->velocity.y) < this->minVelocity)
	{
		this->velocity.y = 0.f;
	}

	this->sprite.move(this->velocity);
}

void Player::move(const float dir_x, const float dir_y)
{
	//Acceleration
	this->velocity.x += dir_x * this->acceleration;
	if (this->isAirborne == false) {
		this->velocity.y += dir_y * this->accelerationY;
		this->isAirborne = true;
	}

	//Limiting Velocity
	if (std::abs(this->velocity.x) > this->maxVelocity) 
	{
		this->velocity.x = this->maxVelocity * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
	
	if (std::abs(this->velocity.y) > this->maxVelocityY || this->isAirborne == true)
	{
		this->velocity.y = this->maxVelocityY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}
	
}

const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;
	
	if (this->animationSwitch)
	{
		this->animationSwitch = false;
	}

	return anim_switch;
}
const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}


void Player::changeAirborne()
{
	this->isAirborne = false;
}

bool Player::checkAirborne()
{
	bool state = isAirborne;
	return state;
}

void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}
