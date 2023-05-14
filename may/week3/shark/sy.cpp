#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define MAX 21

struct Node {
	int y, x;
};

int N, M;
int MAP[MAX][MAX];
int tmp[MAX][MAX];
int mxg, mxrcnt, mxy, mxx;

vector<Node> rainbow; // 무지개

int visited[MAX][MAX];
int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			int now = MAP[i][j];
			if (!now) {
				MAP[i][j] = 6;
				Node tmp = { i, j };
				rainbow.push_back(tmp);
			}
		}
	}
}

bool outRange(int y, int x) {
	return y < 0 || x < 0 || y >= N || x >= N;
}

void CLEAR() {
	int ed = rainbow.size();
	for (int i = 0; i < ed; i++) {
		Node now = rainbow[i];
		visited[now.y][now.x] = 0;
	}
}

bool isBig(int cnt, int rcnt, int y, int x) {
	if (cnt < 2 || cnt == rcnt)
		return 0;
	if (cnt > mxg)
		return 1;
	else if (cnt == mxg) {
		if (rcnt > mxrcnt)
			return 1;
		else if (rcnt == mxrcnt) {
			if (y > mxy)
				return 1;
			else if (y == mxy) {
				if (x > mxx)
					return 1;
			}
		}
	}
	return 0;
}

void bfs(int y, int x) {
	int num = MAP[y][x];

	int tmpMAP[MAX][MAX] = { 0, };
	tmpMAP[y][x] = num;

	queue<Node> q;
	q.push({ y, x });

	CLEAR();
	visited[y][x] = 1;

	int area = 1;
	int rcnt = 0;
	while (!q.empty())
	{
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (outRange(ny, nx))
				continue;
			if (visited[ny][nx])
				continue;
			if (MAP[ny][nx] == -1)
				continue;
			if (MAP[ny][nx] == num || MAP[ny][nx] == 6) {
				if (MAP[ny][nx] == 6) rcnt++;
				area++;
				visited[ny][nx] = 1;
				tmpMAP[ny][nx] = num;
				q.push({ ny, nx });
			}
		}
	}
	if (isBig(area, rcnt, y, x)) {
		mxg = area;
		mxrcnt = rcnt;
		mxy = y;
		mxx = x;
		memcpy(tmp, tmpMAP, sizeof(tmpMAP));
	}
}

void REMOVE() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!tmp[i][j])
				continue;
			MAP[i][j] = 0;
		}
	}
	memset(tmp, 0, sizeof(tmp));
}

void findBgroup() {
	mxg = -1, mxrcnt = -1, mxy = -1, mxx = -1;
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j] == -1 || MAP[i][j] == 6 || !MAP[i][j] || visited[i][j])
				continue;
			
			bfs(i, j);
		}
	}
}

void gravity() {
	for (int j = 0; j < N; j++) {
		int h = N - 1;
		for (int i = N - 1; i >= 0; i--) {
			if (!MAP[i][j])
				continue;
			if (MAP[i][j] == -1) {
				h = i - 1;
				continue;
			}
			int tmp = MAP[i][j];
			MAP[i][j] = 0;
			MAP[h][j] = tmp;
			h--;
			if (h < 0) h = 0;
		}
	}
}

void rotate() {
	int temp[MAX][MAX] = { 0, };
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			temp[i][j] = MAP[j][N - i - 1];
		}
	}
	memcpy(MAP, temp, sizeof(MAP));
}

void findRainbow() {
	rainbow.clear();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j] == 6)
				rainbow.push_back({ i, j });
		}
	}
}

void solve() {
	int score = 0;
	while (true)
	{
		// #1. 가장 큰 블록 그룹 찾기
		findBgroup();
		if (mxg == -1)
			break;
		// #2. 블록 제거
		REMOVE();
		score += (mxg * mxg);
		// #3. 중력 작용
		gravity();
		// #4. 반시계 90도 회전
		rotate();
		// #5. 다시 중력 구현
		gravity();
		// #6. 무지개 좌표 갱신
		findRainbow();
	}
	cout << score << '\n';
}

int main() {
	fastIO;
	input();
	solve();
	return 0;
}
