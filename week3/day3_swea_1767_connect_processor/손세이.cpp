#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

// 설계
// 그냥 DFS 돌면서
// 1. core를 하나씩 탐색하고, 
// 2. 전원이 연결된 core, 그때 전선의 길이는 얼마인지 받아
// 3. 모든 코어를 탐색 했을 때, 현재까지 전원이 연결된 코어가 이전에 있던 답보다 많다면 최대수와 전선의 최소 길이 갱신
// 4. 만약 개수가 같으면 전선 길이 중 짧은 값으로 갱신

struct Node {
	int y;
	int x;
};

int N;
int MAP[13][13];
int maxCnt;
int minDist = 21e8;
vector<Node> core;

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

void INIT() {
	memset(MAP, 0, sizeof(MAP));
	core.clear();
	maxCnt = 0;
	minDist = 21e8;
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 1) {
				if (i == 0 || j == 0 || i == N - 1 || j == N - 1) continue;
				core.push_back({ i, j });
			}
		}
	}
}

// now : 몇번째 코어를 탐색 중인가?, cnt : 몇개의 코어가 연결되었는가?, lineDist : 전선의 길이
void dfs(int now, int cnt, int lineDist) {
	// 기저 조건
	if (now == core.size()) {
		if (cnt > maxCnt) {
			maxCnt = cnt;
			minDist = lineDist;
		}
		else if (cnt == maxCnt) 
			minDist = min(minDist, lineDist);
		
		return;
	}
	// 재귀 구성
	for (int i = 0; i < 4; i++) {
		vector<Node> line;
		int flag = 0;

		int ny = core[now].y;
		int nx = core[now].x;
		
		while (true)
		{
			// 전원이 연결되면 반복문 종료
			if (ny == 0 || nx == 0 || ny == N - 1 || nx == N - 1) {
				flag = 1;
				break;
			}
			ny += ydir[i];
			nx += xdir[i];
			
			if (MAP[ny][nx] == 0)
				line.push_back({ ny, nx }); // 전선 길이 추가
			else
				break;
		}
		if (flag) {
			// 추가된 전선만큼 지도에 2로 표시
			for (int j = 0; j < line.size(); j++)
				MAP[line[j].y][line[j].x] = 2;

			dfs(now + 1, cnt + 1, lineDist + line.size());
			// 복구
			for (int j = 0; j < line.size(); j++)
				MAP[line[j].y][line[j].x] = 0;
		}
	}
	dfs(now + 1, cnt, lineDist);

}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// reset
		INIT();
		// input
		input();
		// solve
		dfs(0, 0, 0);
		// output
		int ans = minDist;
		cout << '#' << tc << ' ' << ans << '\n';
	}

	return 0;
}
