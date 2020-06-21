#pragma once
#include"Snake.h"
#include"SFML\System.hpp"
#include"SFML\Window.hpp"
#include"SFML\Graphics.hpp"

class SfSnake
{
private:
	Snake snake;
	
	//body.front() is the head
	std::vector<sf::RectangleShape> body;


	void updateBody(std::vector<std::vector<int>>& map);
public:
	vector<tuple<int, int>> ori_pos;

	vector<tuple<int, int>> new_pos;

	SfSnake(std::queue<std::tuple<int, int>> startingPos);

	void setPosition(std::queue<std::tuple<int, int>> pos);

	void update(std::vector<std::vector<int>>& map);

	void draw(sf::RenderTarget* targetWindow);
};

