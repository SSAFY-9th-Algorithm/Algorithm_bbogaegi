#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

/*
dijkstra를 이용할 것
- 4방향 + 터널
*/

struct Node {
	int y;
	int x;
	int cost;

	bool operator<(Node next) const {
		return cost < next.cost;
	}
};

int N, M; // 지도 한 변의 길이, 터널 개수
int mat[40][40];
int dist[40][40];
Node tunnel[40][40];

int ydir[] = { -1, 1, 0, 0 };
int xdir[] = { 0, 0, -1, 1 };

void reset() {
	memset(mat, 0, sizeof(mat));
	memset(dist, 0, sizeof(dist));
}

void input() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> mat[i][j];
			dist[i][j] = 21e8;
		}
	}
	for (int i = 0; i < M; i++) {
		int ay, ax, by, bx, c;
		cin >> ay >> ax >> by >> bx >> c;
		tunnel[ay][ax] = { by, bx, c };
		tunnel[by][bx] = { ay, ax, c };
	}
}

void dijkstra(int sy, int sx) {
	priority_queue<Node> pq;
	dist[sy][sx] = 1;
	pq.push({ sy, sx, 1 });
	while (!pq.empty()) {
		Node now = pq.top();
		pq.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (ny < 1 || nx < 1 || ny > N || nx > N)
				continue;
			if (dist[ny][nx])
				continue;
			int diff = mat[ny][nx] - mat[now.y][now.x];
//			if (diff < dist[ny][nx])
			if (diff > 0)
				dist[ny][nx] = dist[now.y][now.x] + (mat[ny][nx] - mat[now.y][now.x]) * 2;
			else
				dist[ny][nx] = dist[now.y][now.x];
			pq.push({ ny, nx, dist[ny][nx] });
		}
		//
		// if (tunnel[now.y][now.x].cost)/// 터널이 존재하면
		//	if ({tunnel[now.y][now.x].y || })
		//터널 이용 경우도 추가해줘야함
	}
}

int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// reset
		reset();
		// input
		input();
		// solve
		dijkstra(1, 1);
		// output
		cout << "#" << tc << " " << dist[N][N] << '\n';
	}
}
