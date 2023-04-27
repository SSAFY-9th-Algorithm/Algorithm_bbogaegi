#include <iostream>
#include <vector>
using namespace std;

int N;
int MaxScore = -21e8;
vector<int>path;
int visited[9];

int check(vector<int> path) {

	int base[3];
	for (int i = 0; i < path.size(); i++) {
		int playerSkill = path[i];

		if (playerSkill == 0) {

		}else if (playerSkill == 1) {

		}else if (playerSkill == 2) {

		}else if (playerSkill == 3) {

		}else if (playerSkill ==4) {

		}

	}
}

void dfs(int players[9], int level, int outCnt) {

	if (outCnt == 3) {
		for (int i = 0; i < path.size(); i++) {
			cout << path[i] << ' ';
		}cout << endl;

		int score = check(path);
		if (score > MaxScore)
			MaxScore = score;

		return;
	}

	if (level == 4) {
		path.push_back(players[0]);
		if (players[0] == 0)
			dfs(players, level + 1, outCnt);
		else
			dfs(players, level + 1, outCnt + 1);
	}

	for (int i = 1; i < 9; i++) {
		
		if (visited[i] == 1)
			continue;

		visited[i] = 1;
		path.push_back(i);

		if (players[i] == 0) {
			dfs(players, level + 1, outCnt);
			path.pop_back();
			visited[i] = 0;
		}
		else {
			dfs(players, level + 1, outCnt + 1);
			path.pop_back();
			visited[i] = 0;
		}
	}

}

int main() {
	
	cin >> N;
	int players[9];
	for (int i = 0; i < N; i++) {
		cin >> players[i];

		dfs(players, 0, 0);

		MaxScore = -21e8;
		path.clear();
		memset(visited, 0, sizeof(visited));
	}

	return 0;
}
