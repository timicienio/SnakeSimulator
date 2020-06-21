#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "State.h"
#include "EndMenu.h"
#include "Terrain.h"
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <cmath>
#include <sstream>
#include <fstream>
#include <cstring>

class GameState :
	public State
{
private:
	SfSnake* sfsnake;
	sf::Font font;
	int score;
	sf::Text scoreText;
	vector<Terrain> mapBody;
	static const int NUM_MAP = 200;
	int stepsLeft;
	sf::Text stepsText;
	vector<vector<int>> map;
	vector<vector<int>> whole_map[NUM_MAP + 1];
	int cur_map_index;
	EndMenu* endMenu;

	void update();
	void updateMapBody();
	void render();
	void loadmaps(std::vector<std::vector<int>> map[NUM_MAP + 1]);
	std::vector<std::vector<int>> generate_map(std::vector<std::tuple<int, int>> snack);
	queue<tuple<int, int>> get_start_position();
	vector<vector<int>> get_map();

	bool checkInvalidStep();
	bool checkHitWall();
	bool checkHitSelf();
	bool checkEatLonger();
public:
	bool gameOver;
	GameState(std::stack<State*>* states, sf::RenderWindow* window);
	~GameState();
};

