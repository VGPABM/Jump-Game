#include "Game.h"
#include "stdafx.h"

void Game::initWindow()
{

	this->window.create(sf::VideoMode::getDesktopMode(), "Jojo's Bizzare Adventure", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(165);
}

void Game::initPlayer()
{
	this->player = new Player();
}

Game::Game()
{
	this->initWindow();
	this->initPlayer();
}

Game::~Game()
{
	delete this->player;
}

void Game::updateCollision()
{
	//Collision bottom of screen
	
	if (this->player->getGlobalBounds().top + this->player->getGlobalBounds().height > this->window.getSize().y) {
		this->player->changeAirborne();
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getGlobalBounds().left, this->window.getSize().y - this->player->getGlobalBounds().height);
	}
}

void Game::updatePlayer()
{
	this->player->update();
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
				(this->ev.key.code == sf::Keyboard::W && this->player->checkAirborne() == false) ||
				this->ev.key.code == sf::Keyboard::S 				
				)) this->player->resetAnimationTimer();
	}
	this->updatePlayer();

	this->updateCollision();
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::render()
{
	this->window.clear();

	//Render Game
	this->renderPlayer();


	this->window.display();
}

const sf::RenderWindow& Game::getwindow()
{
	// TODO: insert return statement here
	return this->window;
}

