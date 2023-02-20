#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

// 아직 푸는 중 코드 저장용

struct Node {
	int y;
	int x;
	int cost;

	bool operator < (Node next) const {
		if (cost > next.cost)
			return true;
		if (cost < next.cost)
			return false;
		return false;
	}
};

struct Tunnel {
	int sy, sx;
	int ey, ex;
	int cost;
};

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

int N, M;
int MAP[31][31];
vector<Tunnel> tunnel;
int dist[31][31];

void INIT() {
	memset(MAP, 0, sizeof(MAP));
	memset(dist, 0, sizeof(dist));
	tunnel.clear();
}

void dijkstra(int y, int x) {
	priority_queue<Node>pq;
	pq.push({ y, x, 0 });

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			dist[i][j] = 21e8;

	dist[y][x] = 0;

	while (!pq.empty())
	{
		Node now = pq.top();
		pq.pop();

		if (now.cost > dist[now.y][now.x])
			continue;

		for (int j = 0; j < tunnel.size(); j++) {
			if (now.y == tunnel[j].sy && now.x == tunnel[j].sx) {
				int ncost = now.cost + tunnel[j].cost;
				if (ncost < dist[tunnel[j].ey][tunnel[j].ex]) {
					dist[tunnel[j].ey][tunnel[j].ex] = ncost;
					pq.push({ tunnel[j].ey, tunnel[j].ex, ncost });
				}
			}
		}

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			
			if (ny <= 0 || nx <= 0 || ny > N || nx > N)
				continue;

			int ncost;

			if(MAP[now.y][now.x] > MAP[ny][nx])
				ncost = now.cost;
			else if (MAP[now.y][now.x] < MAP[ny][nx]) {
				int tmp = abs(MAP[now.y][now.x] - MAP[ny][nx]);
				ncost = now.cost + (tmp * 2);
			}
			else 
				ncost = now.cost + 1;
			
			if (ncost >= dist[ny][nx])
				continue;
			dist[ny][nx] = ncost;
			pq.push({ ny, nx, ncost });
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			cout << dist[i][j] << ' ';
		cout << '\n';
	}
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// reset
		int ans = 0;
		INIT();
		// input
		cin >> N >> M;
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				cin >> MAP[i][j];
		for (int i = 0; i < M; i++) {
			int Ay, Ax, By, Bx, cost;
			cin >> Ay >> Ax >> By >> Bx >> cost;
			tunnel.push_back({  Ay, Ax , By, Bx , cost });
		}
		// solve
		dijkstra(1,1);
		ans = dist[N][N];
		// output
		cout << '#' << tc << ' ' << ans << '\n';
	}

	return 0;
}
