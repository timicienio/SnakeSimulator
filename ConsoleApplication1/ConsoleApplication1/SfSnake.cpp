#include "SfSnake.h"

static const int UNIT_SIZE = 16;

vector<tuple<int,int>> toVector(queue<tuple<int, int>> q)
{
	vector<tuple<int, int>> re;
	while (!q.empty())
	{
		re.push_back(q.front());
		q.pop();
	}
	return re;
}

void SfSnake::updateBody(std::vector<std::vector<int>>& map)
{
	if (map.at(get<0>(new_pos.back())).at(get<1>(new_pos.back())) == 0)
	{
		body.pop_back();
	}
	body.emplace(body.begin(), sf::Vector2f(UNIT_SIZE - 2, UNIT_SIZE - 2));
	body.front().setFillColor(sf::Color::Green);
	body.front().setPosition(get<0>(new_pos.back()) * UNIT_SIZE + 1, get<1>(new_pos.back()) * UNIT_SIZE + 1);
}

SfSnake::SfSnake(std::queue<std::tuple<int, int>> startingPos)
	:snake(startingPos)
{
	new_pos = toVector(startingPos);
	for (int i = 0; !startingPos.empty(); i++)
	{
		body.emplace_back(sf::Vector2f(UNIT_SIZE - 2, UNIT_SIZE - 2));
		body.back().setFillColor(sf::Color::Green);
		body.back().setPosition(std::get<0>(startingPos.front()) * UNIT_SIZE + 1, std::get<1>(startingPos.front()) * UNIT_SIZE + 1);
		startingPos.pop();
	}
}

void SfSnake::setPosition(std::queue<std::tuple<int, int>> pos)
{
	
}

void SfSnake::update(std::vector<std::vector<int>>& map)
{
	ori_pos = new_pos;
	new_pos = toVector(snake.nextPosition(map));
	updateBody(map);
}

void SfSnake::draw(sf::RenderTarget* targetWindow)
{
	for (int i = 0; i < body.size(); i++)
	{
		targetWindow->draw(body.at(i));
	}
}
