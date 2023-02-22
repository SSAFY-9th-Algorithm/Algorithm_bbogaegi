#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

/*
dijkstra를 이용할 것
- 4방향 + 터널
터널을 반복문으로 확인할 때 시간초과 발생
-> 터널에 대한 처리를 다시해줘야할 것 같다.
-> 부분부분 오답도 
*/

struct Node {
	int y;
	int x;
	int cost;

	bool operator<(Node next) const {
		return cost > next.cost;
	}
};

int N, M; // 지도 한 변의 길이, 터널 개수
int mat[40][40];
int dist[40][40];
vector<Node> tunnel[40][40];

int ydir[] = { -1, 1, 0, 0 };
int xdir[] = { 0, 0, -1, 1 };


void reset() {
	memset(mat, 0, sizeof(mat));
	memset(dist, 0, sizeof(dist));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			tunnel[i][j].clear();
		}
	}
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
		tunnel[ay][ax].push_back({ by, bx, c });
		tunnel[by][bx].push_back({ ay, ax, c });
	}
}

void dijkstra(int sy, int sx) {
	priority_queue<Node> pq;
	dist[sy][sx] = 1;
	pq.push({ sy, sx, 1 });
	while (!pq.empty()) {
		Node now = pq.top();
		pq.pop();
		if (now.cost > dist[now.y][now.x])
			continue;
		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (ny < 1 || nx < 1 || ny > N || nx > N)
				continue;
			if (dist[ny][nx] != 21e8)
				continue;
			int diff = mat[ny][nx] - mat[now.y][now.x];
			if (diff < 0) {
				diff = 0;
			}
			else if (diff == 0)
				diff = 1;
			else {
				diff *= 2;
			}
			diff += dist[now.y][now.x];
			if (dist[ny][nx] < diff)
				continue;
			dist[ny][nx] = diff;
			pq.push({ ny, nx, dist[ny][nx] });
		}
		for (int i = 0; i < tunnel[now.y][now.x].size(); i++) {
			Node next = tunnel[now.y][now.x][i];
			if (next.cost + dist[now.y][now.x] > dist[next.y][next.x])
				continue;
			dist[next.y][next.x] = next.cost + dist[now.y][now.x];
			pq.push({ next.y, next.x, dist[next.y][next.x] });
		}
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
		cout << "#" << tc << " " << dist[N][N] - 1 << '\n';
	}
}
