#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
using ll = long long;

/*
  설계
  1. 각 그룹의 칸수를 구하면 번호를 기록
  2. 각 그룹사이의 경계면 구하기
  3. 점수 구하기
  4. 회전
  5. 3라운드까지 반복
*/

struct Node {
	int y, x;
};

struct Group {
	int num; // 몇 번으로 이루어져 있는가?
	int cnt; // 몇 칸?
	int boundary[1000];
};

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

int N;
int MAP[30][30][2]; // 0: 기본 맵, 1: 그룹 맵
int COPY[30][30];
int visited[30][30];

Group g[1000];
int MAX;
ll ans;

void print(int idx) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%2d ", MAP[i][j][idx]);
		}
		printf("\n");
	}
}

void printGroup() {
	for (int i = 1; i < MAX; i++) {
		printf("group[%d]-%d : ",i, g[i].num);
		for (int j = 1; j < MAX; j++)
			printf("%d ", g[i].boundary[j]);
		printf("\n");
	}
}

void init() {
	memset(visited, 0, sizeof(visited));
	memset(g, 0, sizeof(g));
	MAX = -1;
}

void input() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) 
			scanf("%d", &MAP[i][j][0]);
}

bool outRange(int y, int x) {
	return y < 0 || x < 0 || y >= N || x >= N;
}

ll getSum(Group A, Group B, int idx) {	
	ll score = (A.cnt + B.cnt) * A.num * B.num * A.boundary[idx];
	return score;
}

// 그룹 칸수 + 번호 붙이기
void bfs(int y, int x, int idx) {
	queue<Node> q;
	q.push({ y, x });

	visited[y][x] = 1;
	MAP[y][x][1] = idx;
	int num = MAP[y][x][0];

	int cnt = 1;
	while (!q.empty())
	{
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			// 범위 확인
			if (outRange(ny, nx))
				continue;
			// 방문 확인
			if (visited[ny][nx])
				continue;
			// 같은 곳이 아니면 continue
			if (MAP[ny][nx][0] != num)
				continue;
			// 그룹 번호 붙여주기
			MAP[ny][nx][1] = idx;
			cnt++;
			visited[ny][nx] = 1;
			q.push({ ny, nx });
		}
	}
	g[idx].cnt = cnt;
}

void getBoundary(int y, int x) {
	queue<Node> q;
	q.push({ y, x });

	int visit[30][30] = { 0, };
	visit[y][x] = 1;
	visited[y][x] = 1;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (outRange(ny, nx))
				continue;
			if (visit[ny][nx])
				continue;
			if (MAP[ny][nx][1] != MAP[y][x][1]) {
				int idx = MAP[y][x][1];
				int num = MAP[ny][nx][1];
				// idx번 그룹과 num번 그룹 사이의 경계면의 개수 기록
				g[idx].boundary[num]++; 
				continue;
			}
			visited[ny][nx] = 1;
			visit[ny][nx] = 1;
			q.push({ ny, nx });
		}
	}
}

void cpyMAP() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			MAP[i][j][0] = COPY[i][j];
}

void rClock(int y, int x, int mid) {
	for (int i = y; i < y + mid; i++)
		for (int j = x; j < x + mid; j++) {
			int ty = i - y, tx = j - x;
			int ny = tx, nx = mid - ty - 1;
			COPY[ny + y][nx + x] = MAP[i][j][0];
		}
}

// 회전하기
void rotate() {
	int mid = N / 2;
	memset(COPY, 0, sizeof(COPY));
	// 십자 반시계 회전
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if(i == mid || j == mid)
				COPY[N - j - 1][i] = MAP[i][j][0];
		}
	}
	// 나머지 부분 시계방향 회전
	rClock(0, 0, mid);
	rClock(0, mid + 1, mid);
	rClock(mid + 1, 0, mid);
	rClock(mid + 1, mid + 1, mid);
	int de = 1;
	cpyMAP();
}

void getGroup() {
	int idx = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j][0] && !visited[i][j]) {
				int num = MAP[i][j][0];
				bfs(i, j, idx);
				g[idx].num = num;
				idx++;
			}
		}
	}
	MAX = idx;
}

void getB() {
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j][0] && !visited[i][j]) {
				getBoundary(i, j);
			}
		}
	}
}

void getScore() {
	for (int i = 1; i < MAX; i++) {
		for (int j = i + 1; j < MAX; j++) {
			Group A = g[i];
			Group B = g[j];

			if (A.boundary[j] == 0 || B.boundary[i] == 0)
				continue;
			ans += getSum(A, B, j);
		}
	}
}

void solve() {
	for (int t = 0; t <= 3; t++) {
		int de = 1;
		init();
		// 각 그룹의 칸수를 구하고 번호를 기록
		getGroup();
		//print(1);

		// 다른 그룹과의 경계면을 구하자
		getB();
		//printGroup();
		// 초기 점수를 구한다
		getScore();
		// 회전
		rotate();
	}
}

int main() {
	input();
	solve();
	printf("%lld", ans);
	return 0;
}
