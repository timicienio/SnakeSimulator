// #include <Windows.h>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const pair<int, int> MAP_SIZE = make_pair(50, 50); // including boundary
const int NUM_FOOD = 2; // food each round
const int SCORE_RANGE = 3; // range of score of each food, from 1 to SCORE_RANGE

int main()
{
    vector<pair<int, int>> barriers;

    // position of barrier, to lazy to make it random, can modify it urself
    barriers.push_back(make_pair(6, 6));
    barriers.push_back(make_pair(14, 10));
    barriers.push_back(make_pair(20, 11));
    barriers.push_back(make_pair(21, 31));
    barriers.push_back(make_pair(25, 12));
    barriers.push_back(make_pair(33, 8));
    barriers.push_back(make_pair(9, 36));
    barriers.push_back(make_pair(27, 16));
    barriers.push_back(make_pair(11, 44));
    barriers.push_back(make_pair(15, 22));
    barriers.push_back(make_pair(18, 22));
    barriers.push_back(make_pair(19, 1));
    barriers.push_back(make_pair(1, 30));
    barriers.push_back(make_pair(42, 45));
    barriers.push_back(make_pair(39, 38));
    barriers.push_back(make_pair(45, 26));
    barriers.push_back(make_pair(30, 8));
    barriers.push_back(make_pair(17, 27));
    barriers.push_back(make_pair(7, 20));
    barriers.push_back(make_pair(8, 33));

    vector<vector<int>> tempMap;

    for (size_t j = 0; j < MAP_SIZE.second; j++) {
        tempMap.push_back(vector<int>());
        if (j == 0 || j == MAP_SIZE.second - 1) {
            for (size_t k = 0; k < MAP_SIZE.first; k++) {
                tempMap[j].push_back(-1);
            }
        }

        else {
            for (size_t k = 0; k < MAP_SIZE.second; k++) {
                if (k == 0 || k == MAP_SIZE.first - 1) {
                    tempMap[j].push_back(-1);
                } else {
                    tempMap[j].push_back(0);
                }
            }
        }
    }

    for (size_t i = 0; i < barriers.size(); i++) {
        tempMap[barriers[i].first][barriers[i].second] = -1;
    }

    random_device rd;
    minstd_rand gen = minstd_rand(rd());
    uniform_int_distribution<int> dis(1, MAP_SIZE.first - 2);
    uniform_int_distribution<int> dis2(1, MAP_SIZE.first - 2);
    uniform_int_distribution<int> foodScoreDis(1, SCORE_RANGE);

    string filename = "";
    for (size_t i = 0; i < 100; i++) {
        vector<vector<int>> map = tempMap;
        filename = "map_" + to_string(i + 101);
        cout << "writing " << filename << "\n";

        // if (!fp)
        // {
        //     cout << "fail\n";
        // }

        // else
        {
            bool success = false;
            pair<int, int> foodPos;
            for (size_t j = 0; j < NUM_FOOD; j++) {
                success = false;
                cout << j << "\n";
                while (!success) {
                    foodPos = make_pair(dis(gen), dis2(gen));
                    cout << "try put food at " << foodPos.first << "," << foodPos.second << "\n";

                    if (map[foodPos.first][foodPos.second] == 0) {
                        map[foodPos.first][foodPos.second] = foodScoreDis(gen);
                        cout << "put food at " << foodPos.first << "," << foodPos.second << "\n";
                        success = true;
                    }
                }
            }
        }

        fstream fp;
        fp.open(filename, ios::out);

        for (size_t j = 0; j < MAP_SIZE.second; j++) {
            for (size_t k = 0; k < MAP_SIZE.first; k++) {
                if (!k == 0) {
                    fp << " ";
                }
                fp << to_string(map[j][k]);
            }
            if (j != MAP_SIZE.second - 1) fp << "\n";
        }

        fp.close();
    }

    // system("pause");

    return 0;
}