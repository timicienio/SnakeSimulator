#pragma once
#include<stack>
#include"SfSnake.h"

class State
{
protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
public:
	State(std::stack<State*>* states, sf::RenderWindow* window);

	virtual void update() = 0;
	virtual void render() = 0;
};

