#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
using namespace std;

struct Node {
	int y;
	int x;
};

int N;
int mat[17][17];
int visited[17][17];
int ans = 0;
int ydir[4] = {0, 0, 1, 1};
int xdir[4] = {0, 1, 0, 1};

void input() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			scanf("%d", &mat[i][j]);
	}
}

void dfs(int y, int x, int dir) {
	int temp[17][17] = { 0 };
	if (y == N && x == N) {
		ans++;
		return;
	}
	int i;
	for (i = 1; i < 3; i++) {
		if (dir < 3 && dir != i)
			continue;
		int ny = y + ydir[i];
		int nx = x + xdir[i];
		if (ny < 1 || nx < 1 || ny > N || nx > N)
			continue;
		if (visited[ny][nx] || mat[ny][nx])
			continue;
		visited[ny][nx] = 1;
		dfs(ny, nx, i);
		visited[ny][nx] = 0;
	}
	if (i != 3)
		return;
	memcpy(temp, visited, sizeof(visited));
	int d;
	for (d = 1; d < 4; d++) {
		int ny = y + ydir[d];
		int nx = x + xdir[d];
		if (ny < 1 || nx < 1 || ny > N || nx > N)
			break;
		if (visited[ny][nx] || mat[ny][nx])
			break;
		visited[ny][nx] = 1;
	}
	if (d == 4)
		dfs(y + ydir[3], x + xdir[3], 3);
	memcpy(visited, temp, sizeof(temp));
}

int main() {
	input();
	visited[1][1] = 1;
	visited[1][2] = 1;
	dfs(1, 2, 1);
	printf("%d\n", ans);
}
