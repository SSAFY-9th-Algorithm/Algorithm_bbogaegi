#define _CRT_SECURE_NO_WARNINGS
#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

struct Node {
	int y, x;
};

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

int N, M;
int MAP[21][21];
int DAT[21][21];
int flag = 1;
int num;
int ans;

Node robot[11];
int dist[21][21];
int used[401];

void init() {
	num = 0;
	memset(DAT, 0, sizeof(DAT));
	memset(MAP, 0, sizeof(MAP));
	memset(dist, 0, sizeof(dist));
	ans = 21e8;
}

void input() {
	cin >> M >> N;
	if (N == 0 && M == 0) {
		flag = 0;
		return;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			char ch;
			cin >> ch;
			if (ch == 'x') MAP[i][j] = -1;
			else if (ch == '*') {
				MAP[i][j] = ++num;
				robot[num] = { i, j };
			}
			else if (ch == 'o') {
				robot[0] = { i, j };
				MAP[i][j] = 0;
			}
			else MAP[i][j] = 0;
			
		}
	}
}

bool outRange(int y, int x) {
	return y < 0 || x < 0 || y >= N || x >= M;
}

bool bfs(int idx) {
	queue<Node> q;
	int y = robot[idx].y, x = robot[idx].x;
	q.push({ y, x });

	int visited[21][21] = { 0, };
	memset(visited, -1, sizeof(visited));
	visited[y][x] = 0;

	while (!q.empty())
	{
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (outRange(ny, nx))
				continue;
			if (visited[ny][nx] != -1)
				continue;
			if (MAP[ny][nx] == -1)
				continue;
			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny, nx });
		}
	}
	for (int i = 0; i <= num; i++) {
		Node now = robot[i];
		dist[idx][i] = visited[now.y][now.x];
		if (dist[idx][i] == -1)
			return 0;
	}
	return 1;
}

void dfs(int now, int cnt, int cost) {
	if (cnt == num) {
		if (cost < ans)
			ans = cost;
		return;
	}

	for (int i = 1; i <= num; i++) {
		if (used[i])
			continue;
		used[i] = 1;
		dfs(i, cnt + 1, cost + dist[now][i]);
		used[i] = 0;
	}
}

void solve() {
	int f = 1;
	for (int i = 0; i <= num; i++) {
		if (!bfs(i)) {
			f = 0;
			break;
		}		
	}
	if (!f) cout << -1 << '\n';
	else {
		dfs(0, 0, 0);
		cout << ans << '\n';
	}
}

int main() {
	//freopen("input.txt", "r", stdin);
	fastIO;
	while (1)
	{
		init();
		input();
		if (flag == 0)
			break;
		solve();
	}

	return 0;

}
