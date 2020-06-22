#include "GameState.h"

GameState::GameState(std::stack<State*>* states, sf::RenderWindow* window)
	:State(states, window), stepsLeft(8000), cur_map_index(1), score(0), gameOver(false), endMenu(nullptr)
{
	loadmaps();
	sfsnake = new SfSnake(get_start_position());
	map = generate_map(sfsnake->new_pos);
	updateMapBody();
	font.loadFromFile("comicSans.ttf");
	scoreText = sf::Text("Score:" + to_string(score), font, 64);
	scoreText.setPosition(20.f, 900.f);
	stepsText = sf::Text("Steps Left:" + to_string(stepsLeft), font, 64);
	stepsText.setPosition(300.f, 900.f);
	mapText = sf::Text("Map:" + to_string(cur_map_index), font, 64);
	mapText.setPosition(780.f, 900.f);
}

GameState::~GameState()
{
	if (endMenu)
	{
		delete endMenu;
	}
	delete sfsnake;
}

void GameState::update()
{
	if (stepsLeft > 0 && !gameOver)
	{
		stepsLeft--;
		stepsText.setString("Steps Left:" + to_string(stepsLeft));
		sfsnake->update(map);
		if (checkInvalidStep() || checkHitWall() || checkHitSelf() || checkEatLonger())
		{
			gameOver = true;
			return;
		}
		if (map[get<0>(sfsnake->new_pos.back())] [get<1>(sfsnake->new_pos.back())]> 0)
		{
			score += map[get<0>(sfsnake->new_pos.back())][get<1>(sfsnake->new_pos.back())];
			cur_map_index++;
			try
			{
				if (cur_map_index <= 100)
				{
					map = generate_map(sfsnake->new_pos);
				}
				else
				{
					map = generate_map2(sfsnake->new_pos);
				}
			}
			catch (out_of_range & oor)
			{
				cout << oor.what() << endl;
				endMenu = new EndMenu(&font, "Clear!");
				gameOver = true;
			}
			updateMapBody();
			scoreText.setString("Score:" + to_string(score));
			mapText.setString("Map:" + to_string(cur_map_index));
		}
	}
}

void GameState::updateMapBody()
{
	mapBody.clear();
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map.at(i).size(); j++)
		{
			if (map.at(i).at(j) != 0)
			{
				mapBody.emplace_back(map.at(i).at(j), i, j, &font);
			}
		}
	}
}

void GameState::render()
{
	sfsnake->draw(window);
	for (int i = 0; i < mapBody.size(); i++)
	{
		mapBody.at(i).draw(window);
	}
	window->draw(scoreText);
	window->draw(stepsText);
	window->draw(mapText);
	if (gameOver)
	{
		endMenu->draw(window);
	}
}

void GameState::loadmaps()
{
	fstream file;
	char buffer[150];
	string fname;
	for (int i = 1; i < 201; i++) {
		if (i < 10)
			fname = "00" + to_string(i);
		else if (i < 100)
			fname = "0" + to_string(i);
		else
			fname = to_string(i);
		file.open("map/maps/map_" + fname, ios::in);
		if (!file) {
			cout << "no file" << endl;
		}
		else {
			do {
				vector<int> tempv;
				file.getline(buffer, sizeof(buffer));
				const char* d = " ";
				char* row;
				row = strtok(buffer, d);
				while (row) {
					string s = row;
					int temp = stoi(s);
					tempv.push_back(temp);
					row = strtok(NULL, d);
				}
				whole_map[i].push_back(tempv);
			} while (!file.eof());
		}
		file.close();
	}
}


std::vector<std::vector<int>> GameState::generate_map(std::vector<std::tuple<int, int>> snake) throw(out_of_range)
{
	if (cur_map_index > NUM_MAP)
	{
		throw out_of_range("No more maps");
	}
	queue<tuple<int, int>> snack;
	for (int i = snake.size() - 1; i >= 0; i--)
	{
		snack.push(snake.at(i));
	}
	tuple<int, int> position;
	int row, col;
	int flag3 = 0;
	int flag5 = 0;
	int flag7 = 0;
	int flagall = 0;

	//尋找地圖得分點位置
	for (int m = 0; m < 50; m++) {
		for (int n = 0; n < 50; n++) {
			if (whole_map[cur_map_index][m][n] == 1) {
				row = m;
				col = n;
				position = make_tuple(m, n);
			}
		}
	}

	//判斷得分點有沒有在蛇身上
	int flag = 0;
	queue<tuple<int, int>> tempsnack = snack;
	while (!tempsnack.empty() && flag == 0) {
		if (tempsnack.front() == position) {
			flag = 1;
		}
		tempsnack.pop();
	}
	if (flag == 0)
		return whole_map[cur_map_index];
	else {
		//      3*3找新得分點
		for (int i = row - 1; i < row + 2; i++) {
			if (i > 0 && i < 49 && flag3 == 0) {
				for (int j = col - 1; j < col + 2; j++) {
					if (j > 0 && j < 49 && flag3 == 0) {
						tempsnack = snack;
						flag = 0;
						position = make_tuple(i, j);
						//每一個點跟蛇的位置比較，有找到
						while (!tempsnack.empty() && flag == 0) {
							if (tempsnack.front() == position) {
								flag = 1;
							}
							tempsnack.pop();
						}
						if (flag == 0) {
							flag3 = 1;//在3*3中找到可以放點的地方
							row = i;//新點index
							col = j;
							break;
						}
					}
					if (flag3 == 1)
						break;
				}
			}
			if (flag3 == 1) {
				break;
			}
		}
		if (flag3 == 1) {  //3*3找到
			vector<vector<int>> newmap;
			for (int i = 0; i < 50; i++) {
				vector<int> tempv;
				for (int j = 0; j < 50; j++) {
					if (i == 0 || i == 49) {
						tempv.push_back(-1);
					}
					else {
						if (i == row && j == col) {
							tempv.push_back(1);
						}
						else if (j == 0 || j == 49)
							tempv.push_back(-1);
						else
							tempv.push_back(0);
					}
				}
				newmap.push_back(tempv);
			}
			return newmap;
		}
		else if (flag3 == 0 && flag5 == 0) { //5*5找得分點
			for (int i = row - 2; i < row + 3; i++) {
				if (i > 0 && i < 49 && flag5 == 0) {
					for (int j = col - 2; j < col + 3; j++) {
						if (j > 0 && j < 49 && flag5 == 0) {
							tempsnack = snack;
							flag = 0;
							position = make_tuple(i, j);
							//每一個點跟蛇的位置比較，有找到
							while (!tempsnack.empty() && flag == 0) {
								if (tempsnack.front() == position) {
									flag = 1;
								}
								tempsnack.pop();
							}
							if (flag == 0) {
								flag5 = 1;//在5*5中找到可以放點的地方
								row = i;
								col = j;
								break;
							}
						}
						if (flag5 == 1)
							break;
					}
				}
				if (flag5 == 1) {
					break;
				}
			}
		}
		if (flag5 == 1) {  //5*5找到
			vector<vector<int>> newmap;
			for (int i = 0; i < 50; i++) {
				vector<int> tempv;
				for (int j = 0; j < 50; j++) {
					if (i == 0 || i == 49) {
						tempv.push_back(-1);
					}
					else {
						if (i == row && j == col) {
							tempv.push_back(1);
						}
						else if (j == 0 || j == 49)
							tempv.push_back(-1);
						else
							tempv.push_back(0);
					}
				}
				newmap.push_back(tempv);
			}
			return newmap;
		}
		else if (flag3 == 0 && flag5 == 0 && flagall == 0) {
			for (int i = 0; i < 50; i++) {
				if (i > 0 && i < 49 && flagall == 0) {
					for (int j = 0; j < 50; j++) {
						if (j > 0 && j < 49 && flagall == 0) {
							tempsnack = snack;
							flag = 0;
							position = make_tuple(i, j);
							//每一個點跟蛇的位置比較，有找到
							while (!tempsnack.empty() && flag == 0) {
								if (tempsnack.front() == position) {
									flag = 1;
								}
								tempsnack.pop();
							}
							if (flag == 0) {
								flag5 = 1;//在5*5中找到可以放點的地方
								row = i;
								col = j;
								break;
							}
						}
						if (flagall == 1)
							break;
					}
				}
				if (flagall == 1) {
					break;
				}
			}
		}
		if (flagall == 1) {
			vector<vector<int>> newmap;
			for (int i = 0; i < 50; i++) {
				vector<int> tempv;
				for (int j = 0; j < 50; j++) {
					if (i == 0 || i == 49) {
						tempv.push_back(-1);
					}
					else {
						if (i == row && j == col) {
							tempv.push_back(1);
						}
						else if (j == 0 || j == 49)
							tempv.push_back(-1);
						else
							tempv.push_back(0);
					}
				}
				newmap.push_back(tempv);
			}
			return newmap;
		}
	}
}

vector<int> GameState::findthree(int row, int col, queue<tuple<int, int>> snack) {
	int flag3 = 0;
	int flag = 0;
	vector<int> result;
	tuple<int, int> position; //暫時的點
	queue<tuple<int, int>> tempsnack = snack;
	for (int i = row - 1; i < row + 2; i++) { //原本點的3*3為範圍
		if (i > 0 && i < 49 && flag3 == 0) {
			for (int j = col - 1; j < col + 2; j++) {
				if (j > 0 && j < 49 && flag3 == 0) {
					tempsnack = snack;
					flag = 0;
					position = make_tuple(i, j);
					//每一個點跟蛇的位置比較，有找到
					while (!tempsnack.empty() && flag == 0) {
						if (tempsnack.front() == position) {
							flag = 1;
						}
						tempsnack.pop();
					}
					if (flag == 0) {
						flag3 = 1;//在3*3中找到可以放點的地方
						row = i;//新點index
						col = j;
						break;
					}
				}
			}
			if (flag3 == 1)
				break;
		}
	}
	if (flag3 == 1) {
		result.push_back(flag3);
		result.push_back(row);
		result.push_back(col);
	}
	else if (flag3 == 0) {
		result.push_back(flag3);
		result.push_back(0);
		result.push_back(0);
	}
	return result;
}

vector<int> GameState::findfive(int row, int col, queue<tuple<int, int>> snack) {
	int flag5 = 0;
	int flag = 0;
	vector<int> result;
	tuple<int, int> position; //暫時的點
	queue<tuple<int, int>> tempsnack = snack;
	for (int i = row - 2; i < row + 3; i++) { //原本點的3*3為範圍
		if (i > 0 && i < 49 && flag5 == 0) {
			for (int j = col - 2; j < col + 3; j++) {
				if (j > 0 && j < 49 && flag5 == 0) {
					tempsnack = snack;
					flag = 0;
					position = make_tuple(i, j);
					//每一個點跟蛇的位置比較，有找到
					while (!tempsnack.empty() && flag == 0) {
						if (tempsnack.front() == position) {
							flag = 1;
						}
						tempsnack.pop();
					}
					if (flag == 0) {
						flag5 = 1;//在5*5中找到可以放點的地方
						row = i;//新點index
						col = j;
						break;
					}
				}
			}
			if (flag5 == 1)
				break;
		}
	}
	if (flag5 == 1) {
		result.push_back(flag5);
		result.push_back(row);
		result.push_back(col);
	}
	else if (flag5 == 0) {
		result.push_back(flag5);
		result.push_back(0);
		result.push_back(0);
	}
	return result;
}

vector<int> GameState::findall(int row, int col, queue<tuple<int, int>> snack) {
	int flagall = 0;
	int flag = 0;
	vector<int> result;
	tuple<int, int> position; //暫時的點
	queue<tuple<int, int>> tempsnack = snack;
	for (int i = 0; i < 50; i++) { //原本點的3*3為範圍
		if (i > 0 && i < 49 && flagall == 0) {
			for (int j = 0; j < 50; j++) {
				if (j > 0 && j < 49 && flagall == 0) {
					tempsnack = snack;
					flag = 0;
					position = make_tuple(i, j);
					//每一個點跟蛇的位置比較，有找到
					while (!tempsnack.empty() && flag == 0) {
						if (tempsnack.front() == position) {
							flag = 1;
						}
						tempsnack.pop();
					}
					if (flag == 0) {
						flagall = 1;//在5*5中找到可以放點的地方
						row = i;//新點index
						col = j;
						break;
					}
				}
			}
			if (flagall == 1)
				break;
		}
	}
	if (flagall == 1) {
		result.push_back(flagall);
		result.push_back(row);
		result.push_back(col);
	}
	else if (flagall == 0) {
		result.push_back(flagall);
		result.push_back(0);
		result.push_back(0);
	}
	return result;
}

vector<vector<int>> GameState::generate_map2(std::vector<std::tuple<int, int>> snake) throw(out_of_range) 
{
	if (cur_map_index > NUM_MAP)
	{
		throw out_of_range("No more maps");
	}
	tuple<int, int> positionONE, positionTWO;
	int row1 = 0, row2 = 0, col1 = 0, col2 = 0;
	//    int flag3=0;
	//    int flag5=0;
	//    int flag7=0;
	//    int flagall=0;
	queue<tuple<int, int>> snack;
	for (int i = snake.size() - 1; i >= 0; i--)
	{
		snack.push(snake.at(i));
	}
		//尋找地圖兩個得分點位置
	for (int m = 0; m < 50; m++) {
		for (int n = 0; n < 50; n++) {
			if (whole_map[cur_map_index][m][n] == 1) {
				row1 = m;
				col1 = n;
				positionONE = make_tuple(m, n);
			}
			if (whole_map[cur_map_index][m][n] == 2) {
				row2 = m;
				col2 = n;
				positionTWO = make_tuple(m, n);
			}
		}
	}
	//先調整得分點2，再調整得分點1
		//判斷得分點有沒有在蛇身上
	int twoOnSnack = 0;
	int oneOnSnack = 0;
	vector<int> result;
	queue<tuple<int, int>> tempsnack = snack;
	while (!tempsnack.empty()) {
		if (tempsnack.front() == positionTWO) {
			twoOnSnack = 1;
			cout << "two on snack" << endl;
		}
		if (tempsnack.front() == positionONE) {
			oneOnSnack = 1;
			cout << "one on snack" << endl;
		}
		tempsnack.pop();
	}
	if (oneOnSnack == 0 && twoOnSnack == 0) { //兩個都不在蛇身上
		return whole_map[cur_map_index];
	}
	if (twoOnSnack == 1) { //如果得分點2在蛇身上
		result = findthree(row2, col2, snack); //從3*3開始找
		if (result[0] == 1) {
			twoOnSnack = 0;
			row2 = result[1];
			col2 = result[2];
		}
		else if (result[0] == 0) {
			result = findfive(row2, col2, snack); //從5*5開始找
			if (result[0] == 1) {
				twoOnSnack = 0;
				row2 = result[1];
				col2 = result[2];
			}
			else if (result[0] == 0) {
				result = findall(row2, col2, snack); //全部找
				if (result[0] == 1) {
					twoOnSnack = 0;
					row2 = result[1];
					col2 = result[2];
				}
			}
		}
	}
	if (oneOnSnack == 1) {
		result = findthree(row1, col1, snack); //從3*3開始找
		if (result[0] == 1) {
			oneOnSnack = 0;
			row1 = result[1];
			col1 = result[2];
		}
		else if (result[0] == 0) {
			result = findfive(row1, col1, snack); //從5*5開始找
			if (result[0] == 1) {
				oneOnSnack = 0;
				row1 = result[1];
				col1 = result[2];
			}
			else if (result[0] == 0) {
				result = findall(row1, col1, snack); //全部找
				if (result[0] == 1) {
					oneOnSnack = 0;
					row1 = result[1];
					col1 = result[2];
				}
			}
		}
	}
	if (oneOnSnack == 0 && twoOnSnack == 0) {  //得分點1、2都不在蛇身上
		vector<vector<int>> newmap;
		for (int i = 0; i < 50; i++) {
			vector<int> tempv;
			for (int j = 0; j < 50; j++) {
				if (i == 0 || i == 49) {
					tempv.push_back(-1);
				}
				else {
					if (i == row1 && j == col1) {
						tempv.push_back(1);
					}
					else if (i == row2 && j == col2)
						tempv.push_back(2);
					else if (j == 0 || j == 49)
						tempv.push_back(-1);
					else
						tempv.push_back(0);
				}
			}
			newmap.push_back(tempv);
		}
		return newmap;
	}
}

queue<tuple<int, int>> GameState::get_start_position()
{
	queue<tuple<int, int>> re;

	tuple<int, int> pos1(1, 1);
	tuple<int, int> pos2(1, 2);
	tuple<int, int> pos3(1, 3);
	tuple<int, int> pos4(1, 4);
	tuple<int, int> pos5(1, 5);

	re.push(pos1);
	re.push(pos2);
	re.push(pos3);
	re.push(pos4);
	re.push(pos5);

	return re;
}

vector<vector<int>> GameState::get_map()
{
	vector<vector<int>> re;

	return re;
}

bool GameState::checkInvalidStep()
{
	int one_step_limit = 1;
	one_step_limit -= abs(get<0>(sfsnake->ori_pos.back()) - get<0>(sfsnake->new_pos.back()));
	one_step_limit -= abs(get<1>(sfsnake->ori_pos.back()) - get<1>(sfsnake->new_pos.back()));
	if (one_step_limit != 0) {
		endMenu = new EndMenu(&font, "Invalid Step.");
		return true;
	}
	return false;
}

bool GameState::checkHitWall()
{
	if (map[get<0>(sfsnake->new_pos.back())][get<1>(sfsnake->new_pos.back())] == -1) {
		endMenu = new EndMenu(&font, "Hit wall.");
		return true;
	}
	return false;
}

bool GameState::checkHitSelf()
{
	for (int i = 0; i < sfsnake->new_pos.size() - 1; i++) {
		if (get<0>(sfsnake->new_pos.at(i)) == get<0>(sfsnake->new_pos.back()) && get<1>(sfsnake->new_pos.at(i)) == get<1>(sfsnake->new_pos.back())) {
			endMenu = new EndMenu(&font, "Hit self.");
			return true;
		}
	}
	return false;
}

bool GameState::checkEatLonger()
{
	if (map[get<0>(sfsnake->new_pos.back())][get<1>(sfsnake->new_pos.back())] > 0) {
		if (sfsnake->new_pos.size() != sfsnake->ori_pos.size() + 1) {
			endMenu = new EndMenu(&font, "Invalid eat length.");
			return true;
		}
	}
	else {
		if (sfsnake->new_pos.size() != sfsnake->ori_pos.size()) {
			endMenu = new EndMenu(&font, "Invalid length");
			return true;
		}
	}
	return false;
}
