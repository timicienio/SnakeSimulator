#include "Game.h"

using namespace std;


int main() {
	Game game;

	game.run();

	//for (int i = 0; i < step_limit; i++) {
	//	ori_pos = new_pos;
	//	new_pos = snake.nextPosition(map);

	//	int new_head_x = get<0>(new_pos.back());
	//	int new_head_y = get<1>(new_pos.back());
	//	cout << i << ": " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "|" << map[new_head_x][new_head_y] << "$" << point << "\n";

	//	// Walk one step
	//	int one_step_limit = 1;
	//	one_step_limit -= abs(get<0>(ori_pos.back()) - new_head_x);
	//	one_step_limit -= abs(get<1>(ori_pos.back()) - new_head_y);
	//	if (one_step_limit != 0) {
	//		cout << " A: Invalid step... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";
	//		break;
	//	}

	//	// Hit wall
	//	if (map[new_head_x][new_head_y] == -1) {
	//		cout << " B: GAME OVER! Hit wall... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";
	//		break;
	//	}

	//	// Hit self
	//	queue<tuple<int, int>> tmp_queue = new_pos;
	//	bool ifGameOver = false;
	//	for (int i = 0; i < new_pos.size() - 1; i++) {
	//		if (get<0>(tmp_queue.front()) == new_head_x && get<1>(tmp_queue.front()) == new_head_y) {
	//			cout << " C: GAME OVER! Hit yourself... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";
	//			ifGameOver = true;
	//			break;
	//		}
	//		tmp_queue.pop();
	//	}
	//	if (ifGameOver)
	//		break;
	//	// Check teleport
	//	// TBD...

	//	// Count point and check eat longer
	//	if (map[new_head_x][new_head_y] > 0) {
	//		if (new_pos.size() != ori_pos.size() + 1) {
	//			cout << " D: Invalid eat length... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";
	//			break;
	//		}

	//		point += map[new_head_x][new_head_y];
	//		map = generate_map(whole_map, ++cur_map_index, new_pos);
	//	}
	//	else {
	//		if (new_pos.size() != ori_pos.size()) {
	//			cout << " E: Invalid length... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";
	//			break;
	//		}
	//	}
	//	if (cur_map_index > NUM_MAP) {
	//		break;
	//	}
	//}
	//cout << " | Final: " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "$" << point << "\n";

	//system("pause");
	return 0;
}
