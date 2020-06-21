#pragma once
#include"SfSnake.h"

class EndMenu
{
private:
	sf::Font* font;

	sf::Text text;
	string info;

public:
	EndMenu(sf::Font* font, string info);
	void draw(sf::RenderWindow* window);
};

