#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "EndMenu.h"
#include "Terrain.h"
#include "SfSnake.h"

class GameState :
	public State
{
private:
	SfSnake* sfsnake;
	sf::Font font;
	int score;
	sf::Text scoreText;
	sf::Text mapText;
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
	void loadmaps();
	std::vector<std::vector<int>> generate_map(std::vector<std::tuple<int, int>> snack) throw(out_of_range);
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

