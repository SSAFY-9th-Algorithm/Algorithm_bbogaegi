#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N;
int MAP[20][20];
int ans;

int ydir[] = { 0,1,1 };
int xdir[] = { 1,0,1 };

void dfs(int y, int x, int dir) {
	if (y == N-1 && x == N-1) {
		ans++;
		return;
	}

	for (int i = 0; i < 3; i++) {
		// 현재 방향이 가로면 세로 불가
		if (dir == 0 && i == 1)
			continue;
		// 현재 방향이 세로면 가로 불가
		if (dir == 1 && i == 0)
			continue;

		int ny = y + ydir[i];
		int nx = x + xdir[i];

		if (ny < 0 || nx < 0 || ny >= N || nx >= N)
			continue;
		if (MAP[ny][nx])
			continue;
		if (i == 2 && (MAP[y + 1][x] || MAP[y][x + 1]))
			continue;
		dfs(ny, nx, i);
		
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> MAP[i][j];

	dfs(0, 1, 0);
	cout << ans;

	return 0;
}
