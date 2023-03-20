#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int y;
	int x;
	int dir;
};

int N, M;
int mat[51][51];
int num = 0;
int visited[51][51];

// 상 우 하 좌
int ydir[] = { -1, 0, 1, 0 };
int xdir[] = { 0, 1, 0, -1 };
Node robot;

int main(void) {
	cin >> N >> M;
	cin >> robot.y >> robot.x >> robot.dir;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			cin >> mat[i][j];
	}
	visited[robot.y][robot.x] = 1;
	num++;
	while (true) {
		int nextdir = (robot.dir - 1) < 0 ? 3 : robot.dir - 1;
		int flag = 0;
		for (int i = 0; i < 4; i++) {
			int ny = robot.y + ydir[nextdir];
			int nx = robot.x + xdir[nextdir];
			if (ny < 0 || nx < 0 || ny >= N || nx >= M || mat[ny][nx] || visited[ny][nx]) {
				nextdir = (nextdir - 1) < 0 ? 3 : nextdir - 1;
				continue;
			}
			visited[ny][nx] = 1;
			num++;
			robot.y = ny;
			robot.x = nx;
			robot.dir = nextdir;
			flag = 1;
			break;
		}
		if (flag == 0) {
			nextdir = (robot.dir + 2) % 4;
			int ny = robot.y + ydir[nextdir];
			int nx = robot.x + xdir[nextdir];
			if (ny < 0 || nx < 0 || ny >= N || nx >= M || mat[ny][nx]) {
				break;
			}
			if (visited[ny][nx] == 0)
				num++;
			visited[ny][nx] = 1;
			robot.y = ny;
			robot.x = nx;
		}
	}
	cout << num << '\n';
}
