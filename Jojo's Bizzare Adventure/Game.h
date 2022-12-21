#pragma once
#include"stdafx.h"
#include"Player.h"
#include "Bullet.h"
#include "Obstacle.h"
#include "Enemy.h"
#include "Health.h"
#include "Coin.h"


class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;

	//Player
	Player* player;

	//Stuff on screen
	float spawnTimer;
	float spawnBulletMax;
	float spawnBulletTimer;
	float spawnTimerMax;
	float spawnEnemyTimer;
	float spawnEnemyMax;
	float spawnCoinTimer;
	float spawnCoinMax;
	float spawnHealthTimer;
	float spawnHealthMax;
	sf::Texture temp;
	std::vector<Obstacle*> obstacles;
	std::vector<Enemy*> enemies;
	std::vector<Coin*> coins;
	std::vector<Health*> healths;

	//GUI
	sf::Font font;
	sf::Font point;
	sf::Text TitleTex;
	sf::Text pointText;
	sf::Text coinText;
	sf::Text hpBar;

	sf::Text gameOverText;

	//Player GUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//World
	sf::Texture worldBackgroundtex;
	sf::Sprite worldBackground;


	//System
	unsigned points;
	unsigned coinAmm;

	
	//Resources
	std::vector<Bullet*> bullets;

	//Music
	sf::Music deathTheme;
	sf::Music mainTheme;
	sf::SoundBuffer bufferOra;
	sf::Sound Ora;
	sf::SoundBuffer bufferDamage;
	sf::Sound Damage;
	sf::SoundBuffer bufferHealth;
	sf::Sound HealthSound;
	sf::SoundBuffer bufferCoin;
	sf::Sound CoinSound;
	sf::SoundBuffer bufferGameOver;
	sf::Sound GameOverSound;

	//Init Things
	void initSound();
	void initGUI();
	void initWindow();
	void initPlayer();
	void initObstacles();
	void initHealth();
	void initCoins();
	void initEnemy();
	void initWorld();
	void initSystem();

public:
	//Functions
	void run();
	Game();
	virtual ~Game();

	//Update Things
	void updatePollEvents();
	void updateBullets();
	void updateCollision();
	void updatePlayer();
	void updateGUI();
	void updateObstacles();
	void updateHealth();
	void updateCoins();
	void updateEnemy();
	void updateCombat();
	void update();
	void updateWorld();

	void gameOver();


	//RenderStuff
	void renderWorld();
	void renderPlayer();
	void renderGUI();
	void render();

	const sf::RenderWindow& getwindow();
	
};


