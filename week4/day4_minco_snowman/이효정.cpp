#include <iostream>
#include <queue>
#include <climits>
using namespace std;

/*
맵이 들어올 때 정보를 바꿈
=> dist가 1일때는 증가하지 않으므로 0으로 바꿔줌
=> 0인 공간을 오를때는 1이 증가해야하므로 바꿔주고
=> 눈사람과 보석의 좌표는 미리 저장해둔다
=> 눈사람의 위치부터 dijkstra를 돌린다.

dijkstra는 항상 dist배열이 있어야하며,
dist배열은 시작 위치는 0 나머지는 MAX값으로 초기화되어 있어야한다.
*/

struct Node {
	int y;
	int x;
	int cost;
	
	bool operator<(Node next) const {
		return cost > next.cost;
	}
};

Node snowman;
Node jewel;
int N, M; // 세로 가로

int dist[50][50];
int mat[50][50];

int ydir[] = { 0, 0, -1, 1 };
int xdir[] = { -1, 1, 0, 0 };

void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			dist[i][j] = INT_MAX;
			cin >> mat[i][j];
			if (mat[i][j] == 2)
				snowman = { i, j, 0 };
			else if (mat[i][j] == 3)
				jewel = { i, j, 0 };
			if (mat[i][j] == 0)
				mat[i][j] = 1;
			else
				mat[i][j] = 0; // 땅이 있는 곳은 다 0으로 만들어줌
		}
	}
}

void dijkstra() {
	priority_queue<Node> pq;
	pq.push({ snowman.y, snowman.x, 0 });
	dist[snowman.y][snowman.x] = 0;
	while (!pq.empty()) {
		Node now = pq.top();
		pq.pop();
		if (dist[now.y][now.x] < now.cost)
			continue;
		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= M)
				continue;

			// 좌우로 이동하는데 바닥이 없으면 진행할 수 없음
			if (i < 2 && mat[ny][nx])
				continue;
			int nCost = dist[now.y][now.x] + mat[ny][nx];
			if (nCost >= dist[ny][nx])
				continue;
			dist[ny][nx] = nCost;
			pq.push({ ny, nx, nCost });
		}
	}

}

int main() {
	input();
	dijkstra();
	if (dist[jewel.y][jewel.x] == 0)
		dist[jewel.y][jewel.x] = 1;
	cout << dist[jewel.y][jewel.x] << '\n';
}
