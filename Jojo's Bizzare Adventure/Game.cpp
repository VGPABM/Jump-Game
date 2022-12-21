#include "Game.h"
#include "stdafx.h"

void Game::initSound()
{
	this->mainTheme.openFromFile("Resources/Sound/maintheme.ogg");
	mainTheme.play();
	mainTheme.setLoop(true);
	mainTheme.setVolume(30.f);

	this->deathTheme.openFromFile("Resources/Sound/deaththeme2.ogg");
	deathTheme.setLoop(true);

	this->bufferOra.loadFromFile("Resources/Sound/Ora_Loud.ogg");
	this->Ora.setBuffer(bufferOra);
	this->Ora.setVolume(20.f);

	this->bufferDamage.loadFromFile("Resources/Sound/minecraftoof.ogg");
	this->Damage.setBuffer(bufferDamage);
	this->Damage.setVolume(500.f);

	this->bufferHealth.loadFromFile("Resources/Sound/healthsound.ogg");
	this->HealthSound.setBuffer(bufferHealth);
	this->HealthSound.setVolume(100.f);

	this->bufferCoin.loadFromFile("Resources/Sound/coincollect.ogg");
	this->CoinSound.setBuffer(bufferCoin);
	this->CoinSound.setVolume(100.f);

	this->bufferGameOver.loadFromFile("Resources/Sound/gameover2.ogg");
	this->GameOverSound.setBuffer(bufferGameOver);
	this->GameOverSound.setVolume(100.f);
}

void Game::initGUI()
{
	//Load Font
	if (!this->font.loadFromFile("Resources/Font/SF Fedora Titles Shadow Italic.ttf")) std::cout << "failed to load font" << std::endl;
	if (!this->point.loadFromFile("Resources/Font/SF Fedora Shadow.ttf")) std::cout << "failed to load font" << std::endl;

	//Init Point text
	this->pointText.setFont(this->point);
	this->pointText.setCharacterSize(30);
	this->pointText.setPosition(this->window.getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f -300, 30.f);
	this->pointText.setFillColor(sf::Color::White);

	//Init TitleText
	this->TitleTex.setFont(this->font);
	this->TitleTex.setCharacterSize(50);
	this->TitleTex.setFillColor(sf::Color::White);
	this->TitleTex.setString("Jojo Bizzare Jump");

	//init Player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 30.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(this->window.getSize().x - 317, 30.f));
	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

	//Init Game Over Text
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(100);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setPosition(this->window.getSize().x /2.f - this->gameOverText.getGlobalBounds().width/2.f,
		this->window.getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);
	this->gameOverText.setString("Jotaro Died");

	//Init Coin Text
	this->coinText = this->pointText;
	this->coinText.setPosition(pointText.getPosition().x + 300, 30.f);

	//Init Indicator healthbar
	this->hpBar.setFont(this->point);
	this->hpBar.setCharacterSize(25);
	this->hpBar.setPosition(sf::Vector2f(this->window.getSize().x - 75, 30.f));
	this->coinText.setFillColor(sf::Color::White);
}

void Game::initWindow()
{
	this->window.create(sf::VideoMode::getDesktopMode(), "Jojo's Bizzare Adventure", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(165);
}



void Game::initPlayer()
{
	this->player = new Player();
	this->spawnBulletMax = 20.f;
	
}

void Game::initObstacles()
{
	this->spawnTimerMax = 60.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initHealth()
{
	this->spawnHealthMax = 480.f;
	this->spawnHealthTimer = this->spawnHealthMax;
}

void Game::initCoins()
{
	this->spawnCoinMax = 240.f;
	this->spawnCoinTimer = this->spawnCoinMax;
}

void Game::initEnemy()
{
	this->spawnEnemyMax = 480.f;
	this->spawnEnemyTimer = this->spawnEnemyMax;
}

void Game::initWorld()
{
	if(!this->worldBackgroundtex.loadFromFile("Resources/Images/world-background.jpg"))std::cout<<"error bg cuy";
	this->worldBackground.setTexture(this->worldBackgroundtex);
}

void Game::initSystem()
{
	this->points = 0;
}

void Game::run()
{
	if (this->player->getHp() == 0) {
		mainTheme.setLoop(false);
		mainTheme.stop();
		
		this->gameOver();
	}
	else {
		this->update();
	}
	this->render();
	
}

Game::Game()
{
	this->initWindow();
	this->initPlayer();
	this->initGUI();
	this->initSound();
	this->initWorld();
	this->initSystem();
	this->initHealth();
	this->initCoins();
	this->initObstacles();
	this->initEnemy();
}

Game::~Game()
{
	delete this->player;

	for (auto* i : this->obstacles)
	{
		delete i;
	}
	for (auto* i : this->enemies)
	{
		delete i;
	}
	//Delete Bullets
	for (auto* i : this->bullets) {
		delete i;
	}

	for (auto* i : this->coins) {
		delete i;
	}

	for (auto* i : this->healths) {
		delete i;
	}

}

void Game::updatePollEvents()
{
	
}

/*void Game::updateInput()
{
	this->spawnBulletTimer += 0.4f;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->spawnTimer >= this->spawnBulletMax) {
		sf::Vector2f _tempmouse;
		_tempmouse =  sf::Vector2f(sf::Mouse::getPosition(window));
		this->bullets.push_back(new Bullet(this->player->getPos().x, this->player->getPos().y, _tempmouse.x, _tempmouse.y, 10.f));
		this->spawnTimer = 0.f;
	}
}*/

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets) {
		bullet->update();

		if (bullet->getBounds().top + bullet->getBounds().height < 0.f || bullet->getBounds().top + bullet->getBounds().height > this->window.getSize().y ||
			bullet->getBounds().left + bullet->getBounds().width > this->window.getSize().x || bullet->getBounds().left + bullet->getBounds().width < 0
			) {
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}
		++counter;
	}
}

void Game::updateCollision()
{
	//Collision bottom of screen
	
	if (this->player->getGlobalBounds().top + this->player->getGlobalBounds().height > this->window.getSize().y) {
		this->player->changeAirborne();
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getGlobalBounds().left, this->window.getSize().y - this->player->getGlobalBounds().height);
	}
	if (this->player->getGlobalBounds().left < 0.f) {
		this->player->setPosition(0.f, this->player->getGlobalBounds().top);
	}else if (this->player->getGlobalBounds().left + this->player->getGlobalBounds().width >= this->window.getSize().x) {
		this->player->setPosition(this->window.getSize().x - this->player->getGlobalBounds().width, this->player->getGlobalBounds().top);
	}

	if (this->player->getGlobalBounds().top < 0.f) {
		this->player->setPosition(this->player->getGlobalBounds().left, this->window.getSize().y - this->window.getSize().y);
	}
	

}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateGUI()
{
	std::stringstream ss;
	ss <<"Enemy Killed: " << this->points;
	this->pointText.setString(ss.str());
	

	std::stringstream cc;
	cc << "Coin Collected: " << this->coinAmm;
	this->coinText.setString(cc.str());
	

	//Update Player GUI
	float hpPercent;
	hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));

	std::stringstream hh;
	float temp;
	temp = hpPercent * 100; 
	hh << temp;
	this->hpBar.setString(hh.str());


}

void Game::updateObstacles()
{
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax) {
		this->obstacles.push_back(new Obstacle(this->window.getSize().x, rand() % (this->window.getSize().y - 200) + 1.f));
		this->spawnTimer = 0.f;
	}

	unsigned counter = 0;
	for (auto* obstacle : this->obstacles) {
		obstacle->update();

		if (obstacle->getBoundsSquare().top + obstacle->getBoundsSquare().width < 0 || obstacle->getBoundsCircle().top + obstacle->getBoundsCircle().width < 0) {
			delete this->obstacles.at(counter);
			this->obstacles.erase(this->obstacles.begin() + counter);
			//std::cout << this->Enemy.size() << "\n";
		}
		else if (obstacle->getBoundsCircle().intersects(this->player->getGlobalBounds()) || obstacle->getBoundsSquare().intersects(this->player->getGlobalBounds())
			|| obstacle->getBoundsGerman().intersects(this->player->getGlobalBounds())
			)
		{
			this->Damage.play();
			this->player->loseHp(this->obstacles.at(counter)->getDamage());
			delete this->obstacles.at(counter);
			this->obstacles.erase(this->obstacles.begin() + counter);
		}
		++counter;
	}
}

void Game::updateHealth()
{
	//Spawn
	this->spawnHealthTimer += 0.5f;
	if (this->spawnHealthTimer >= this->spawnHealthMax) {
		this->healths.push_back(new Health(this->window.getSize().x, rand() % (this->window.getSize().y - 200) + 1.f));
		this->spawnHealthTimer = 0.f;
	}

	//Enemy Player Collision
	unsigned counter = 0;
	for (auto* health : this->healths) {
		health->update();

		if (health->getBounds().top + health->getBounds().width < 0) {
			delete this->healths.at(counter);
			this->healths.erase(this->healths.begin() + counter);
			//std::cout << this->Enemy.size() << "\n";
		}
		else if (health->getBounds().intersects(this->player->getGlobalBounds()))
		{
			this->player->addHp(this->healths.at(counter)->getHp());
			this->HealthSound.play();
			delete this->healths.at(counter);
			this->healths.erase(this->healths.begin() + counter);
		}
		++counter;
	}
}

void Game::updateCoins()
{
	
	//Spawn
	this->spawnCoinTimer += 0.5f;
	if (this->spawnCoinTimer >= this->spawnCoinMax) {
		this->coins.push_back(new Coin(this->window.getSize().x, rand() % (this->window.getSize().y - 200) + 1.f));
		this->spawnCoinTimer = 0.f;
	}

	//Enemy Player Collision
	unsigned counter = 0;
	for (auto* coin : this->coins) {
		coin->update();

		if (coin->getBounds().top + coin->getBounds().width < 0) {
			delete this->coins.at(counter);
			this->coins.erase(this->coins.begin() + counter);
			//std::cout << this->Enemy.size() << "\n";
		}
		else if (coin->getBounds().intersects(this->player->getGlobalBounds()))
		{
			this->CoinSound.play();
			this->coinAmm += this->coins.at(counter)->getPoints();
			delete this->coins.at(counter);
			this->coins.erase(this->coins.begin() + counter);
		}
		++counter;
	}
}

void Game::updateEnemy()
{
	//Spawn
	this->spawnEnemyTimer += 0.5f;
	if (this->spawnEnemyTimer >= this->spawnEnemyMax) {
		this->enemies.push_back(new Enemy(this->window.getSize().x, rand() % (this->window.getSize().y - 200) + 1.f));
		this->spawnEnemyTimer = 0.f;
	}

	//Enemy Player Collision
	unsigned counter = 0;
	for (auto* enemy : this->enemies) {
		enemy->update();

		if (enemy->getBounds().top + enemy->getBounds().width < 0) {
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			//std::cout << this->Enemy.size() << "\n";
		}
		else if (enemy->getBounds().intersects(this->player->getGlobalBounds()))
		{
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			this->Damage.play();
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		++counter;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_removed = false;
		this->enemies[i]->update();

		for (size_t k = 0; k < this->bullets.size() && !enemy_removed; k++) {
			if (this->bullets[k]->getBounds().intersects(this->enemies[i]->getBounds())) {
				this->points += this->enemies[i]->getPoints();
				this->bullets.erase(this->bullets.begin() + k);
				this->enemies.erase(this->enemies.begin() + i);
				enemy_removed = true;
			}
		}

		if (!enemy_removed) {
			//Remove Enemy at the left of the screen
			if (this->enemies[i]->getBounds().left < -500) {
				this->enemies.erase(this->enemies.begin() + i);
				//std::cout << this->Enemy.size() << "\n";
				enemy_removed = true;
			}
		}
	}
}
void Game::gameOver() {
	int counter = 0;
	while (this->window.pollEvent(this->ev)) {
		std::cout << counter << std::endl;
		if (counter < 10) GameOverSound.play();
		deathTheme.play();
		deathTheme.setVolume(100.f);
		if (this->ev.type == sf::Event::Closed) this->window.close();
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape) this->window.close();
		counter+=1;
	}
}

void Game::update()
{
	//polling windows events
	while (this->window.pollEvent(this->ev))
	{
	
		if (this->ev.type == sf::Event::Closed) this->window.close();
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape) this->window.close();

		if (this->ev.type == sf::Event::KeyReleased && 
			   (this->ev.key.code == sf::Keyboard::A ||
				this->ev.key.code == sf::Keyboard::D ||
				this->ev.key.code == sf::Keyboard::W  ||
				this->ev.key.code == sf::Keyboard::S				
				)) this->player->resetAnimationTimer();

		this->spawnBulletTimer += 0.3f;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->spawnBulletTimer >= this->spawnBulletMax) {
			sf::Vector2f _tempmouse;
			_tempmouse = sf::Vector2f(sf::Mouse::getPosition(window));
			this->bullets.push_back(new Bullet(this->player->getPos().x, this->player->getPos().y, _tempmouse.x, _tempmouse.y, 10.f));
			this->spawnBulletTimer = 0.f;
			this->Ora.play();
		}else if ((sf::Joystick::isButtonPressed(0, 4) || sf::Joystick::isButtonPressed(0, 5) || sf::Joystick::isButtonPressed(0, 1)) && this->spawnBulletTimer >= this->spawnBulletMax) {
			this->bullets.push_back(new Bullet(this->player->getPos().x, this->player->getPos().y, this->player->getPos().x + 5, this->player->getPos().y, 10.f));
			this->spawnBulletTimer = 0.f;
			this->Ora.play();
		}
	}
	//this->updateInput();
	this->updatePlayer();
	this->updateBullets();
	this->updateCollision();
	this->updateObstacles();
	this->updateHealth();
	this->updateCoins();
	this->updateEnemy();
	this->updateCombat();
	this->updateGUI();
	this->updateWorld();
}

void Game::updateWorld()
{

}


void Game::renderWorld()
{
	this->window.draw(this->worldBackground);
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::renderGUI()
{
	this->window.draw(this->TitleTex);
	this->window.draw(this->pointText);
	this->window.draw(this->playerHpBarBack);
	this->window.draw(this->playerHpBar);
	this->window.draw(this->hpBar);
	this->window.draw(this->coinText);
}


void Game::render()
{
	this->window.clear();
	
	//render world
	this->renderWorld();

	//Render Game
	this->renderPlayer();


	//Render Obstacle
	for (auto* Obstacle : this->obstacles)
	{
		Obstacle->render(this->window);
	}

	for (auto* bullet : this->bullets) {
		bullet->render(this->window);
	}

	for (auto* Enemy : this->enemies)
	{
		Enemy->render(this->window);
	}

	for (auto* Coin : this->coins)
	{
		Coin->render(this->window);
	}

	for (auto* Health : this->healths)
	{
		Health->render(this->window);
	}

	this->renderGUI();

	//Game Over
	if (this->player->getHp() <= 0) {
		this->window.draw(this->gameOverText);
	}

	this->window.display();
	
}

const sf::RenderWindow& Game::getwindow()
{
	// TODO: insert return statement here
	return this->window;
}

