#pragma once

#include"SfSnake.h"
#include"GameState.h"

class Game
{
private:
	sf::RenderWindow* window;
	
	sf::Event sfEvent;

	sf::Font font;
	

	sf::Clock clock;
	float dt;

	std::stack<State*> states;

private:
	void update();
	void render();
public:
	Game();

	~Game();

	void run();
};

