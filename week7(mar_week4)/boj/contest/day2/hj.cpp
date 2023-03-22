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
int ydir[] = { -1, 1, 0, 0 };
int xdir[] = { 0, 0, -1, 1 };
int visited[10][10];
int mat[10][10];
vector<Node> cctv5;
CCTV cctv[8];
int ccnum = 0;
int minCnt = 21e8;

int getCount() {
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++)
			if (visited[i][j])
				cnt++;
	}
	return N * M - cnt;
}

void dfs(int now) {
	if (ccnum == now) {
		int temp = getCount();
		if (minCnt > temp)
			minCnt = temp;
		return;
	}
	int origin[10][10];
	memcpy(origin, visited, sizeof(visited));
	CCTV cnow = cctv[now];
	int num = 0;
	for (int i = 0; i < 4; i++) {
		num++;
		int ny = cnow.y + ydir[i];
		int nx = cnow.x + xdir[i];
		while (mat[ny][nx] != 6) {
			visited[ny][nx] = 1;
			ny += ydir[i];
			nx += xdir[i];
		}
		if (cnow.num == 2 && i % 2 == 0)
			continue;
		if (cnow.num == 4 && num < 3)
			continue;
		if (cnow.num == 3 && num < 2) {
			i++;
			continue;
		}
		dfs(now + 1);
		if (cnow.num == 4 || cnow.num == 3) {
			num = 0;
			i = (i + 2) % 4;
		}
		memcpy(visited, origin, sizeof(origin));
	}
}

int main(void) {
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
				visited[ny][nx] = 1;
				ny += ydir[d];
				nx += xdir[d];
			}
		}
	}
	if (ccnum > 0) {
		dfs(0);
		cout << minCnt;
	}
	else {
		cout << getCount();
	}
}
