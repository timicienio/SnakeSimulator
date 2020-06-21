#pragma once
#include"GameState.h"
class Terrain
{
	sf::RectangleShape body;
	sf::Text text;
	sf::Font* font;
	bool hasText;
public:
	Terrain(int num, int x, int y, sf::Font* font)
		:body(sf::Vector2f(16.f - 2, 16.f - 2)), hasText(false)
	{
		body.setPosition(x * 16 + 1, y * 16 + 1);
		this->font = font;
		if (num > 0)
		{
			hasText = true;
			text.setFont(*font);
			text.setString(to_string(num));
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(14);
			text.setPosition(x * 16 + 4, y * 16);
			body.setFillColor(sf::Color::Red);
		}
		else if (num == -1)
		{
			body.setFillColor(sf::Color::White);
		}
	}
	void draw(sf::RenderWindow* window)
	{
		window->draw(body);
		if (hasText)
		{
			window->draw(text);
		}
	}
};

