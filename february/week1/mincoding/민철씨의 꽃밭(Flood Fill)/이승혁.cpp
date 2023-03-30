#include <iostream>
#include <queue>
using namespace std;

int mat[500][500];
int term[500][500];
int MAXday, MAX = -21e8;
int N, M, day = 0;

struct Node {
	int y;
	int x;
};

void bfs(int sy, int sx) {
	queue<Node> q;
	queue<Node> flowers;

	q.push({ sy,sx });
	flowers.push({ sy,sx });
	mat[sy][sx] = 1;

	int ydir[] = { -1,1,0,0 };
	int xdir[] = { 0,0,-1,1 };

	while (!q.empty()) {
		day++;
		int flower = 0;

		// 현재까지 심어진 곳들 진행
		int fsize = flowers.size();
		for (int i = 0; i < fsize; i++) {
			Node fnow = flowers.front();
			int fy = fnow.y;
			int fx = fnow.x;
			flowers.pop();

			if (mat[fy][fx] > term[fy][fx])	continue;
			mat[fy][fx]++;

			if (mat[fy][fx] > 1)flower++;
			flowers.push({ fy,fx });
		}

		if (flower > MAX) {
			MAXday = day;
			MAX = flower;
		}

		int qsize = q.size();

		for (int i = 0; i < qsize; i++) {
			Node now = q.front();
			q.pop();

			for (int i = 0; i < 4; i++) {
				int ny = now.y + ydir[i];
				int nx = now.x + xdir[i];

				if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
				if (mat[now.y][now.x] != 2) continue;

				if (mat[ny][nx] == 0) {
					mat[ny][nx] = 1;
					q.push({ ny,nx });
					flowers.push({ ny,nx });
				}

			}
		}
		
	}
}


int main() {
	int sy, sx;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> term[i][j];
		}
	}
	cin >> sy >> sx;
	bfs(sy, sx);

	cout << MAXday << "일\n" << MAX << "개";
