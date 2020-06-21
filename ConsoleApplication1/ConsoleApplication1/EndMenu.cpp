#include "EndMenu.h"

EndMenu::EndMenu(sf::Font* font, string info) :
	font(font),
	info(info),
	text(info + " Press R to restart", *font, 64)
{
	text.setPosition(20.f, 824.f);
}

void EndMenu::draw(sf::RenderWindow* window)
{
	window->draw(text);
}
