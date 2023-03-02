#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

// dijkstra -> 현재 코드

struct Node {
	int y;
	int x;
	int cost;

	bool operator < (Node next) const {
		return cost < next.cost;
	}
};

int N, M;
int MAP[51][51];
int ans;
int sy, sx, dy, dx;

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

bool outRange(int y, int x) {
	return y < 0 || x < 0 || y >= N || x >= M;
}

void dijkstra() {
	priority_queue<Node>pq;
	pq.push({ sy, sx, 0 });

	int dist[51][51];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			dist[i][j] = 21e8;

	dist[sy][sx] = 0;

	while (!pq.empty())
	{
		Node now = pq.top();
		pq.pop();

		if (now.cost * (-1) > dist[now.y][now.x])
			continue;

		for (int i = 0; i < 4; i++) {
			// 상하 이동
			if (i == 0 || i == 1) {
				for (int j = 1; j < N; j++) { // 갈 수 있는 범위 확인 -> 땅만 갈거임
					int ny = now.y + ydir[i] * j;
					int nx = now.x + xdir[i] * j;

					if (outRange(ny, nx))
						continue;
					if (MAP[ny][nx] == 0) // 땅아니면 안감
						continue;

					int ncost = max(now.cost * (-1), j); // 현재 여기까지 오는데 필요한 MAX장Limit 저장

					if (dist[ny][nx] <= ncost)
						continue;

					dist[ny][nx] = ncost;
					pq.push({ ny, nx, ncost*(-1)});
				}
			}
			if (i == 2 || i == 3) {
				int ny = now.y + ydir[i];
				int nx = now.x + xdir[i];

				if (outRange(ny, nx))
					continue;
				if (MAP[ny][nx] == 0) // 땅아니면 못감
					continue;

				
				if (dist[ny][nx] <= now.cost*(-1))
					continue;

				dist[ny][nx] = now.cost * (-1);
				pq.push({ ny, nx, now.cost });
			}
		}
	}
	cout << dist[dy][dx];
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

	dijkstra();
	return 0;
}
