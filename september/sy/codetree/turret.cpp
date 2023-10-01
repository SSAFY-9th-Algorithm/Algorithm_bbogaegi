#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define MXN 11

struct Node {
	int y, x;
};

struct Tower {
	int y, x;
	int power;
	int time; // 각성 시간
};

bool cmp(Tower a, Tower b) {
	if (a.power != b.power) return a.power < b.power;
	if (a.time != b.time) return a.time > b.time;
	if (a.x + a.y != b.x + b.y) return a.x + a.y > b.x + b.y;
	return a.x > b.x;
}

int ydir[] = { 0,1,0,-1,-1,-1,1,1 };
int xdir[] = { 1,0,-1,0,-1,1,-1,1 };

int N, M, K;
int MAP[MXN][MXN][2]; // 포탑의 power, 각성 시간
vector<Tower> towers;
Node path[MXN][MXN]; // 레이저 공격 경로
int DAT[MXN][MXN]; // 공격 여부 체크

void input() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j][0];
			if (MAP[i][j][0]) {
				Tower now = { i, j, MAP[i][j][0], MAP[i][j][1] };
				towers.push_back(now);
			}
		}
		
}

void getTops() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!MAP[i][j][0]) continue;
			Tower now = { i, j, MAP[i][j][0], MAP[i][j][1] };
			towers.push_back(now);
		}
	}
}

void init() {
	memset(DAT, 0, sizeof(DAT));
	memset(path, 0, sizeof(path));
}

void pickAtk(int t) {
	sort(towers.begin(), towers.end(), cmp);

	Tower now = towers[0];
	now.power += (N + M);
	now.time = t;

	MAP[now.y][now.x][0] += (N + M);
	MAP[now.y][now.x][1] = t;
	DAT[now.y][now.x] = 1;

	towers[0] = now;
}

bool bfs(int sy, int sx, int dy, int dx) {
	queue<Node> q;
	q.push({ sy, sx });

	int visited[MXN][MXN] = { 0, };
	visited[sy][sx] = 1;

	int flag = 0;
	int P = MAP[sy][sx][0];

	while (!q.empty())
	{
		Node now = q.front();
		q.pop();

		if (now.y == dy && now.x == dx) {
			flag = 1;
			break;
		}
		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			ny = (ny + N) % N;
			nx = (nx + M) % M;

			if (visited[ny][nx])
				continue;
			if (!MAP[ny][nx][0])
				continue;

			visited[ny][nx] = 1;
			path[ny][nx] = now;
			q.push({ ny, nx });
		}
	}

	if (!flag) return false;

	Node now = path[dy][dx];
	while (!(now.y == sy && now.x == sx))
	{
		MAP[now.y][now.x][0] -= P / 2;
		if (MAP[now.y][now.x][0] < 0)
			MAP[now.y][now.x][0] = 0;
		DAT[now.y][now.x] = 1;
		Node tmp = path[now.y][now.x];
		now = tmp;
	}
	return 1;
}

void boom(int sy, int sx, int dy, int dx) {
	int P = MAP[sy][sx][0];
	for (int i = 0; i < 8; i++) {
		int ny = dy + ydir[i];
		int nx = dx + xdir[i];

		ny = (ny + N) % N;
		nx = (nx + M) % M;
		
		if (!MAP[ny][nx][0])
			continue;
		if (ny == sy && nx == sx)
			continue;

		DAT[ny][nx] = 1;
		MAP[ny][nx][0] -= P / 2;
		if (MAP[ny][nx][0] < 0)
			MAP[ny][nx][0] = 0;
	}
}

void attack() {
	Tower atk = towers[0];
	int idx = towers.size() - 1;
	Tower tgt = towers[idx];

	DAT[tgt.y][tgt.x] = 1;
	
	if (!bfs(atk.y, atk.x, tgt.y, tgt.x))
		boom(atk.y, atk.x, tgt.y, tgt.x);

	MAP[tgt.y][tgt.x][0] -= atk.power;
	if (MAP[tgt.y][tgt.x][0] < 0)
		MAP[tgt.y][tgt.x][0] = 0;
}

void repair() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!MAP[i][j][0]) continue;
			if (DAT[i][j]) continue;

			MAP[i][j][0]++;
		}
	}
}

void print(int k) {
	cout << k << '\n';
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			cout << MAP[i][j][0] << ' ';
		cout << '\n';
	}
}

void solve() {
	//print(0);
	for (int k = 1; k <= K; k++) {
		init();
		// #1. 공격자 선정
		pickAtk(k);
		// #2. 공격
		attack();
		// #3. 포탑 부서짐

		// #4. 정비
		repair();

		towers.clear();
		getTops();
		//print(k);
		if (towers.size() == 1)
			break;
	}
	
	sort(towers.begin(), towers.end(), cmp);
	int idx = towers.size() - 1;
	int ans = towers[idx].power;

	cout << ans << '\n';
}

int main() {
	//freopen("input.txt", "r", stdin);
	fastIO;
	
	input();
	solve();

	return 0;
}
