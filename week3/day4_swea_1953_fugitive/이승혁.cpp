// 주어진 좌표부터 4방향 탐색
// 0이 아니면 queue 담는다.
// 숫자에 따라서 다음 방향 탐색
// visited == L 인 곳 카운팅

// flood fill 로 1차 시도
// 실패 -> 서로 연결되지 않으면 갈 수 없다
// 조건 추가 -> 만약 다음 좌표에서 now.y now.x를 올 수없다면 continue

// 좌표 정리를 더 깨끗하게 하고싶었는데
// 시간아까워서 고민없이 패스

#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

struct Coord {
	int y, x;
};

int MAP[50][50], visited[50][50];
int N, M, sy, sx, t, res;
int direct1[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
int direct2[6][4] = { {1,0,-1,0},{0,1,0,-1},{-1,0,0,1},
					            {1,0,0,1},{1,0,0 ,-1},{-1,0,0,-1} };

queue<Coord> q;

bool isValid(int y, int x, int index,int ty,int tx) {
	if (MAP[y][x] == 1) {
		for (int i = 0; i < 4; i++) {
			int ny = y + direct1[i][0];
			int nx = x + direct1[i][1];
			if (ny == ty && nx == tx)return true;
		}
	}
	else {
		index -= 2;
		for (int i = 0; i < 3; i += 2) {
			int ny = y + direct2[index][i];
			int nx = x + direct2[index][i + 1];
			if (ny == ty && nx == tx)return true;
		}
	}
	return false;

}

void bfs(int sy, int sx) {

	q.push({ sy,sx });
	visited[sy][sx] = 1;

	while (!q.empty()) {
		Coord now = q.front();
		q.pop();
		if (MAP[now.y][now.x] == 1) {
			for (int i = 0; i < 4; i++) {
				int ny = now.y + direct1[i][0];
				int nx = now.x + direct1[i][1];
				if (nx<0 || ny<0 || ny>N - 1 || nx>M - 1)continue;
				if (MAP[ny][nx] == 0 ) continue;
				if (visited[ny][nx] != 0)continue;
				if (isValid(ny, nx, MAP[ny][nx],now.y,now.x) == false)continue;
				visited[ny][nx] = visited[now.y][now.x] + 1;
				q.push({ ny,nx });
			}
		}
		else {
			int idx = MAP[now.y][now.x] - 2;
			for (int i = 0; i < 3; i += 2) {
				int ny = now.y + direct2[idx][i];
				int nx = now.x + direct2[idx][i + 1];
				if (nx<0 || ny<0 || ny>N - 1 || nx>M - 1)continue;
				if (MAP[ny][nx] == 0) continue;
				if (visited[ny][nx] != 0)continue;
				if (isValid(ny, nx, MAP[ny][nx], now.y, now.x) == false)continue;
				visited[ny][nx] = visited[now.y][now.x] + 1;
				q.push({ ny,nx });
			}
		}

	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (visited[i][j] != 0 && visited[i][j] <= t)res++;
		}
	}

}

int main() {

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		// reset
		memset(MAP, 0, sizeof(MAP));
		memset(visited, 0, sizeof(visited));
		res = 0;
		// input
		cin >> N >> M >> sy >> sx >> t;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cin >> MAP[i][j];
			}
		}
		// solve
		bfs(sy, sx);
		// output
		cout << "#" << tc << " " << res << '\n';
	}
}
