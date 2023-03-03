#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// 최단경로를 찾는 문제가 아니라 상하이동이 중점이다
// 수직 이동 게이지를 가중치라고 생각하면은
// bfs를 이용하려고 봤는데 
// 보석까지 가는 최소 가중치 찾기
// 가중치면 다익스트라?
// 가중치 찾기가 쉽지않다

struct Node {
	int y;
	int x;
	int cost;

	bool operator < (Node next) const {
		return cost > next.cost;
	}
};


int N, M;
int MAP[50][50];
int sy, sx, ey, ex;

void dijkstra(int now) {
	priority_queue<Node>pq;
	pq.push({ sy, sx, 0 });

	int dy[4] = { -1, 1, 0, 0 };
	int dx[4] = { 0, 0, -1, 1 };

	int dist[50][50];
	int MAX = 21e8;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			dist[i][j] = MAX;

	dist[sy][sx] = 0;

	while (!pq.empty()) {
		Node now = pq.top();
		pq.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= M)
				continue;	// 여기까지는 무지성으로 코드를 쳤는데
			// 갈수 있는 경우는 위아래, 좌우인데 각각 조건이 있다
			// 위아래 -> 상하 게이지이하까지 이동가능
			// 좌우 -> 땅이 있어야 가능


		}

	}
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			cin >> MAP[i][j];
		}
	}
}