// 베이스캠프 못지나가게 하라면서
// 못지나가게 하면 답 안나옴
// 왜지?

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <iostream>
using namespace std;

struct Node {
	int y;
	int x;
};

struct Person {
	int idx;
	int y;
	int x;
	int dy;
	int dx;
};

int n, m;
int mat[16][16];
Person p[31];
//상 좌 우 하
int ydir[] = { -1, 0, 0, 1 };
int xdir[] = { 0, -1, 1, 0 };
int maxTime = -21e8;
int times[16][16];

void print_mat(int matt[16][16]) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%2d ", matt[i][j]);
			//cout << matt[i][j] << " ";
		}
		cout << '\n';
	}
}

void bfs(Person start) {
	int visited[16][16] = { 0 };
	queue<Node> q;

	q.push({ start.dy, start.dx });
	visited[start.dy][start.dx] = 1;
	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (ny < 1 || nx < 1 || ny > n || nx > n)
				continue;
			if (visited[ny][nx])
				continue;
			visited[ny][nx] = visited[now.y][now.x] + 1;
			if (mat[ny][nx] == 1) {
				p[start.idx].y = ny;
				p[start.idx].x = nx;
				if (start.idx == 1)
					start.idx *= -1;
				mat[ny][nx] = start.idx;
				return;
			}
			q.push({ ny, nx });
		}
	}
}

void bfs2(Person start) {
	int visited[16][16] = { 0 };
	queue<Node> q;

	q.push({ start.y, start.x });
	visited[start.y][start.x] = start.idx;
	//times[start.y][start.x] = start.idx;
	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (ny < 1 || nx < 1 || ny > n || nx > n)
				continue;
			if (visited[ny][nx] || times[ny][nx])
				continue;
			visited[ny][nx] = visited[now.y][now.x] + 1;
			if (start.dy == ny && start.dx == nx) {
				times[ny][nx] = visited[ny][nx];
				if (maxTime < times[ny][nx])
					maxTime = times[ny][nx];
				//printf("\n\n%d\n", start.idx);
				//print_mat(times);
				//printf("\n\n");

				return;
			}
			q.push({ ny, nx });
		}
	}
}


void input() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &mat[i][j]);
		}
	}
	for (int i = 1; i <= m; i++) {
		p[i] = { i, 0, 0, };
		int y, x;
		scanf("%d %d", &y, &x);
		p[i].dy = y;
		p[i].dx = x;
		bfs(p[i]);
	}
	//mat[p[1].y][p[1].x] *= -1;
	//print_mat(mat);
}

int main(void) {
	input();
	for (int i = 1; i <= m; i++)
		bfs2(p[i]);
	cout << maxTime << '\n';
	return 0;
}
