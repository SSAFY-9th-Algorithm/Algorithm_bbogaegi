#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

struct Node {
	int y, x;
};

int w, h;
int MAP[55][55];
int visited[55][55];

int ydir[] = { -1,1,0,0,-1,-1,1,1 };
int xdir[] = { 0,0,-1,1,-1,1,-1,1 };

void INIT() {
	memset(MAP, 0, sizeof(MAP));
	memset(visited, 0, sizeof(visited));
}

void bfs(int y, int x) {
	queue<Node>q;
	q.push({ y, x });

	visited[y][x] = 1;

	while (!q.empty())
	{
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 8; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (ny < 0 || nx < 0 || ny >= h || nx >= w)
				continue;
			if (visited[ny][nx])
				continue;
			if (!MAP[ny][nx])
				continue;

			visited[ny][nx] = 1;
			q.push({ ny, nx });
		}
	}
}

int main() {
	while (true)
	{
		// reset
		INIT();
		cin >> w >> h;
		if (!w && !h)
			break;
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				cin >> MAP[i][j];

		int cnt = 0;
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++) {
				if (MAP[i][j] && !visited[i][j]) {
					bfs(i, j);
					cnt++;
				}
			}
		cout << cnt << '\n';

	}
	

	return 0;
}
