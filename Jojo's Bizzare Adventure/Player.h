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
	
	//PlayerVariable
	int hp;
	int hpMax;
	int coinAmm;


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
	bool fastfall;
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
	const sf::Vector2f& getPos() const;
	const int& getHp() const;
	const int& getHpMax() const;
	const int& getCoinAmm()const;

	//Modifier
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void resetVelocityY();
	void addCoin(const int coin);
	void setHp(const int hp);
	void addHp(const int value);
	void loseHp(const int value);

	//Function
	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void movey(const float dir_x, const float dir_y);
	void autofall(const float dir_x, const float dir_y);
	void updatePhysics();
	void updateMovement();
	void updateAnimation();
	void update();
	void render(sf::RenderTarget& target);
};

