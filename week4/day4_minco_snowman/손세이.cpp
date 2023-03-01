#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

// 도저히 안되겠어서 옆반 승욱이한테 SOS 보냄...
// 두가지 방법을 제시해줌
// 1. dijkstra -> 원래 시도하던 방법이라 풀어보고 올릴예정
// 2. parametic search -> 현재 코드

int N, M;
int MAP[51][51];
int ans;
int sy, sx, dy, dx;

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

bool outRange(int y, int x) {
	return y < 0 || x < 0 || y >= N || x >= M;
}

bool bfs(int limit) {
	queue<pair<int, int>>q;
	q.push({ sy, sx });

	int visited[51][51] = { 0, };
	visited[sy][sx] = 1;

	while (!q.empty())
	{
		auto now = q.front();
		q.pop();

		if (MAP[now.first][now.second] == 0)
			continue;

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j <= limit; j++) {
				int ny = now.first + ydir[i] * j;
				int nx = now.second + xdir[i] * j;

				if (outRange(ny, nx))
					continue;
				if (visited[ny][nx])
					continue;
				if (j == limit && MAP[ny][nx] == 0)
					continue;

				visited[ny][nx] = 1;
				q.push({ ny, nx });
			}
		}

		for (int i = 2; i < 4; i++) {
			int ny = now.first + ydir[i];
			int nx = now.second + xdir[i];
	
			if (outRange(ny, nx))
				continue;
			if (visited[ny][nx])
				continue;
			if (MAP[ny][nx] == 0)
				continue;

			visited[ny][nx] = 1;
			q.push({ ny, nx });
		}
	}
	if (visited[dy][dx]) return true;
	return false;
}

void psearch() {
	int left = 0;
	int right = N - 1;

	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (bfs(mid)) {
			ans = mid;
			right = mid - 1;
		}
		else
			left = mid + 1;
	}
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 2)
				sy = i, sx = j;
			if (MAP[i][j] == 3)
				dy = i, dx = j;
		}

	psearch();

	cout << ans;
	return 0;
}
