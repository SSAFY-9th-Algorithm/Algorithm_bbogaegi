#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <iostream>
using namespace std;

/*
시뮬레이션으로는 최단 경로를 찾아주기가 힘듦 -> 어떤 방향으로 가야 최단이지? 방향에 대한 처리가 어려움
미리 편의점과의 최단 거리의 베이스캠프를 bfs에서 구해줌
  -> Person 구조체의 y, x는 베이스캠프 위치 | dy, dx는 목적 편의점 위치

1. 모든 사람에 대하여 가장 가까운 베이스캠프 정보를 넣어줌 -> bfs() 함수 안에서 구해줌

2. 낮은 번호의 사람부터 편의점에 위치시키되, maxTime 정보를 업데이트해줌 
   -> bfs2() 함수 안에서, times에 베이스캠프와 편의점 도착 시간을 기록
       => 높은 번호의 사람이 먼저 편의점에 도착해서 낮은 사람의 최단 경로에 그 편의점이 위치하면
          최단 경로를 업데이트(갱신)해줘야할 것 같은데 그 부분이 빠져있음

왜 되지?!
*/

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
			// 나보다 작은 친구의 베이스 캠프는 못지나가도록 고침
			if (mat[ny][nx] && mat[ny][nx] != 1 && mat[ny][nx] < start.idx)
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
	times[start.y][start.x] = start.idx;
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
			if (start.dy == ny && start.dx == nx) { // 나의 편의점인가!
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
