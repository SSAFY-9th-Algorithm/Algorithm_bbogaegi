#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
struct Node {
	int y;
	int x;
};

struct CCTV {
	int num;
	int y;
	int x;
};

int N, M;
int ydir[] = { -1, 0, 1, 0 };
int xdir[] = { 0, -1, 0, 1 };
int visited[10][10];
int mat[10][10];
vector<Node> cctv5;
CCTV cctv[8];
int ccnum = 0; // 5번 CCTV 제외한 CCTV 개수
int minCnt = 21e8;

int check(CCTV now, int dir) {
	int tCnt = 0;
	int ny = now.y + ydir[dir];
	int nx = now.x + xdir[dir];
	while (mat[ny][nx] != 6) {
		if (visited[ny][nx] == 0) {
			tCnt++;
			visited[ny][nx] = 1;
		}
		ny += ydir[dir];
		nx += xdir[dir];
	}
	return tCnt;
}

void dfs(int level, int cnt) {
	if (level == ccnum) {
		int rCnt = N * M - cnt;
		if (minCnt > rCnt)
			minCnt = rCnt;
		return;
	}
	int tempCnt = 0;
	int origin[10][10];
	memcpy(origin, visited, sizeof(visited));
	CCTV now = cctv[level];
	for (int i = 0; i < 4; i++) {
		tempCnt = check(now, i);
		if (now.num == 2) {
			if (i > 1)
				tempCnt += check(now, i - 2);
			else
				tempCnt += check(now, i + 2);
		}
		else if (now.num == 3) {
			tempCnt += check(now, (i + 1) % 4);
		}
		else if (now.num == 4) {
			tempCnt += check(now, (i + 1) % 4);
			tempCnt += check(now, (i + 2) % 4);
		}
		// 이게 있으면 기저조건까지 못가고 끝나는 경우가 생김
		// tc 4
		//if (tempCnt == 0)
		//	continue;
		dfs(level + 1, cnt + tempCnt);
		tempCnt = 0;
		memcpy(visited, origin, sizeof(origin));
	}
}

int main(void) {
	int cnt = 0;
	cin >> N >> M;
	memset(mat[0], 0, sizeof(mat[0]));
	memset(mat[N + 1], 0, sizeof(mat[N + 1]));
	for (int i = 0; i <= N + 1; i++) {
		mat[i][0] = 6;
		mat[i][M + 1] = 6;
		for (int j = 1; j <= M; j++) {
			if (i == 0 || i == N + 1)
				mat[i][j] = 6;
			else {
				cin >> mat[i][j];
				if (mat[i][j]) {
					if (visited[i][j] == 0)
						cnt++;
					visited[i][j] = 1;
					if (mat[i][j] == 5)
						cctv5.push_back({ i, j });
					else if (mat[i][j] < 5)
						cctv[ccnum++] = { mat[i][j], i, j };
				}
			}
		}
	}
	for (int i = 0; i < cctv5.size(); i++) {
		Node now = cctv5[i];
		for (int d = 0; d < 4; d++) {
			int ny = now.y + ydir[d];
			int nx = now.x + xdir[d];
			while (mat[ny][nx] != 6) {
				if (visited[ny][nx] == 0)
					cnt++;
				visited[ny][nx] = 1;
				ny += ydir[d];
				nx += xdir[d];
			}
		}
	}
	if (ccnum > 0) {
		dfs(0, cnt);
		cout << minCnt;
	}
	else {
		cout << N * M - cnt;
	}
}
