#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

/*
dijkstra를 이용할 것
- 4방향 + 터널

문제였던 부분: 동일한 값들도 pq에 넣어줘서 오버헤드가 너무 커지는 문제
	=> 시간초과 해결, next의 dist를 갱신시키는 경우에는 무조건 등호를 포함하여 continue 체크를 해줘야한다.

dist는 최소값으로 갱신이 되어야하기 때문에 dist가 초기값이 아니라면 continue하는 부분은 없어야한다!
visited != dist

feat. 득화 교수님 & 내 깐부 
*/

struct Node {
	int y;
	int x;
	int cost;

	bool operator<(Node next) const {
		return cost > next.cost;
	}
};

struct tNode {
	int ay, ax;
	int by, bx;
	int cost;
};

int N, M; // 지도 한 변의 길이, 터널 개수
int mat[32][32];
int dist[32][32];
vector<tNode> tunnel;

int ydir[] = { -1, 1, 0, 0 };
int xdir[] = { 0, 0, -1, 1 };


void reset() {
	memset(mat, 0, sizeof(mat));
	memset(dist, 0, sizeof(dist));
	tunnel.clear();
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
		tunnel.push_back({ ay, ax, by, bx, c });
	}
}

void dijkstra(int sy, int sx) {
	priority_queue<Node> pq;
	dist[sy][sx] = 0;
	pq.push({ sy, sx, 0 });
	while (!pq.empty()) {
		Node now = pq.top();
		pq.pop();
		if (now.cost > dist[now.y][now.x])
			continue;
		for (int i = 0; i < tunnel.size(); i++) {
			tNode tNow = tunnel[i];
			if (now.y == tNow.ay && now.x == tNow.ax) {
				int tCost = tNow.cost + dist[now.y][now.x];
				if (tCost >= dist[tNow.by][tNow.bx])
					continue;
				dist[tNow.by][tNow.bx] = tCost;
				pq.push({ tNow.by, tNow.bx, tCost });
			}
			else if (now.y == tNow.by && now.x == tNow.bx) {
				int tCost = tNow.cost + dist[now.y][now.x];
				if (tCost >= dist[tNow.ay][tNow.ax])
					continue;
				dist[tNow.ay][tNow.ax] = tCost;
				pq.push({ tNow.ay, tNow.ax, tCost });
			}
		}
		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (ny < 1 || nx < 1 || ny > N || nx > N)
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
			if (dist[ny][nx] <= diff)
				continue;
			dist[ny][nx] = diff;
			pq.push({ ny, nx, dist[ny][nx] });
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
		cout << "#" << tc << " " << dist[N][N] << '\n';
	}
}
