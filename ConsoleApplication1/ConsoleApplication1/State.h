#pragma once
#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <tuple>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <stdexcept>
using namespace std;

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

