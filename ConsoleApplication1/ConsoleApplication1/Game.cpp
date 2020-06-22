#include "Game.h"

void Game::update()
{
	window->pollEvent(sfEvent);
	switch (sfEvent.type)
	{
	default:
		break;
	}
	if (!states.empty())
	{
		states.top()->update();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			delete states.top();
			states.pop();
			states.push(new GameState(&states, window));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window->close();
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
	:dt(0.f)
{
	window = new sf::RenderWindow(sf::VideoMode(1024, 1024), "SnakeSimulator by fredred", sf::Style::Titlebar);

	states.push(new GameState(&states, window));
}

Game::~Game()
{
	while (!states.empty())
	{
		delete states.top();
		this->states.pop();
	}
	delete window;
}

void Game::run()
{
	cout << "Start Simulation" << endl;
	while (window->isOpen())
	{
		float TARGET_FRAMRATE = 20.f;
		dt += clock.restart().asSeconds();
		if (dt >= 1 / TARGET_FRAMRATE)
		{
			update();
			render();
			dt = 0.f;
		}
	}
}
