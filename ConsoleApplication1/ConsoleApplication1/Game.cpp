#include "Game.h"

void Game::update()
{
	window->pollEvent(sfEvent);
	if (!states.empty())
	{
		states.top()->update();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			delete states.top();
			states.pop();
			states.push(new GameState(&states, window));
		}
	}
	else
	{
		window->close();
	}
}

void Game::render()
{
	window->clear();
	if (!states.empty())
	{
		states.top()->render();
	}
	else
	{
		window->close();
	}
	window->display();
}

Game::Game()
	:dt(0)
{
	window = new sf::RenderWindow(sf::VideoMode(1024, 1024), "SnakeSimulator by fredred", sf::Style::Default);

	states.push(new GameState(&states, window));
}

Game::~Game()
{
	while (!states.empty())
	{
		delete states.top();
		this->states.pop();
	}
}

void Game::run()
{
	while (window->isOpen())
	{
		dt += clock.restart().asSeconds();
		float TARGET_FRAMERATE = 20.f;
		if (dt >= 1 / TARGET_FRAMERATE)
		{
			update();
			render();
			dt = 0.f;
		}
	}
}
