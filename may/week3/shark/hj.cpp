#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

struct Node {
	int y;
	int x;
};

/*
	검은색 블록은 -1
	무지개 블록은 0
*/

int N; // 1 ~ 20
int M; // 일반 블록이 가지는 색상 수 1 ~ 5
int mat[25][25]; // 중력을 위해 맵의 가장자리는 -1로
int mark[25][25];
int rused[25][25] = { 0 };
int visited[25][25];

int ydir[] = { -1, 1, 0, 0 };
int xdir[] = { 0, 0, -1, 1 };

int score = 0;
int maxCnt = 0;
int maxRb = 0;

void input(void) {
	scanf("%d %d", &N, &M);
	for (int i = 0; i <= N; i++) {
		mat[0][i] = -1;
		mat[N + 1][i] = -1;
		mat[i][0] = -1;
		mat[i][N + 1] = -1;
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &mat[i][j]);
		}
	}
}

// 1. 가장 큰 그룹 찾기
void bfs(int y, int x) {
	int val = mat[y][x];
	int cnt = 1;
	int rb = 0;
	queue<Node> q;
	int used[25][25] = { 0 };

	q.push({ y,x });
	used[y][x] = 1;
	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		for (int d = 0; d < 4; d++) {
			int ny = now.y + ydir[d];
			int nx = now.x + xdir[d];
			if (mat[ny][nx] < 0 || (mat[ny][nx] && mat[ny][nx] != val))
				continue;
			if (visited[ny][nx] || used[ny][nx])
				continue;
			used[ny][nx] = 1;
			if (mat[ny][nx])
				visited[ny][nx] = 1;
			else
				rb++;
			cnt++;
			q.push({ ny, nx });
		}
	}
	if (cnt < maxCnt || cnt < 2) {
		return;
	}
	if (cnt > maxCnt) {
		maxCnt = cnt;
		maxRb = rb;
	}
	else if (cnt == maxCnt) {
		if (maxRb < rb) {
			maxRb = rb;
		}
		else if (maxRb > rb) { // 무지개 적으면 선택되지 않음
			return;
		}
	}
	memcpy(rused, used, sizeof(used));
}

int findTarget() {
	memset(visited, 0, sizeof(visited));
	maxCnt = 0;
	maxRb = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (visited[i][j])
				continue;
			if (mat[i][j] < 1)
				continue;
			visited[i][j] = 1;
			bfs(i, j);
		}
	}
	return maxCnt;
}

// 2. 그룹 제거 및 점수 획득
void deleteTarget() {
	score += maxCnt * maxCnt;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (rused[i][j])
				mat[i][j] = -10;
		}
	}
}

// 3. 중력 작용
void gravity() {
	vector<int> v;
	for (int col = 1; col <= N; col++) {
		for (int i = 1; i <= N + 1; i++) {
			if (mat[i][col] == -1) {
				int vsize = v.size();
				for (int j = 0; j < vsize; j++) {
					mat[i - 1 - j][col] = v.back();
					v.pop_back();
				}
			}
			else if (mat[i][col] > -1) {
				v.push_back(mat[i][col]);
				mat[i][col] = -10;
			}
		}
	}
}

// 4. 반시계 방향으로 회전
void rotate() {
	int temp[25][25] = { 0 };
	
	memcpy(temp, mat, sizeof(mat));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			mat[i][j] = temp[j][N - i + 1];
		}
	}
}

int main(void) {
	input();
	int ret = findTarget();
	while (ret) {
		deleteTarget();
		gravity();
		rotate();
		gravity();
		ret = findTarget();
	}
	printf("%d\n", score);
}
