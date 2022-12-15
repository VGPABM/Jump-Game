#pragma once
#include"stdafx.h"

enum PLAYER_ANIMATION_STATE{IDLE = 0, IDLE_LEFT, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING, DASH };
enum LAST_PRESSED_KEY{RIGHT = 0, LEFT};

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;

	sf::Clock animationTimer;
	

	//Animation
	short animState;
	sf::IntRect currentFrame;
	short lastPressedkey;
	bool animationSwitch;
	bool isAirborne;


	//Physics
	sf::Vector2f velocity;
	float maxVelocity;
	float minVelocity;
	float acceleration;
	float accelerationY;
	float drag;
	float gravity;
	float maxVelocityY;
	float maxVelocityFallingY;

	//Core
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimation();
	void initPhysics();

public:
	Player();
	virtual ~Player();

	//Accessor
	void changeAirborne();
	bool checkAirborne();
	const bool& getAnimSwitch();
	const sf::FloatRect getGlobalBounds() const;

	//Modifier
	void setPosition(const float x, const float y);
	void resetVelocityY();

	//Function
	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void updatePhysics();
	void updateMovement();
	void updateAnimation();
	void update();
	void render(sf::RenderTarget& target);
};

