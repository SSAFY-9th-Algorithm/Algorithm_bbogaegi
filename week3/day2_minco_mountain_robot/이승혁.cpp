#include <iostream>
#include <cstring>
#include <queue>

using namespace std;
int N, M,pee;
int MAP[30][30];

struct Coord {
	int y, x;
	bool operator < (Coord next) const {
		if (MAP[y][x] < MAP[next.y][next.x])
			return true;
		if (MAP[y][x] > MAP[next.y][next.x])
			return false;
		return false;
	}
};

struct Ternel {
	int sy, sx;
	int ey, ex;
};

Ternel ter[30];
int visited[30][30];
priority_queue<Coord> pq;

void isTernel(int y, int x) {
	// 현재위치가 터널인지 확인해보기
	for (int t = 0; t < M; t++) {
		if (y == ter[t].sy && x == ter[t].sx) {
			visited[ter[t].ey][ter[t].ex] = visited[ter[t].sy][ter[t].sx] + pee;
			return;

		}
		else if (y == ter[t].ey && x == ter[t].ex) {
			visited[ter[t].sy][ter[t].sx] = visited[ter[t].ey][ter[t].ex] + pee;
			return;
		}
	}
}


void bfs(int Y,int X) {
	pq.push({ Y, X});

	int ydir[] = { -1,1,0,0 };
	int xdir[] = { 0,0,-1,1 };

	
	visited[Y][X] = 0;

	while (!pq.empty()) {
		Coord now = pq.top();
		pq.pop();

		// 만약 현재위치가 터널이라면
		// 터널 반대편을 넣는다.
		isTernel(now.y, now.x);

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (ny < 1 || nx < 1 || ny > N || nx > N) continue;
			if (ny == 1 && nx == 1)continue;
			if (visited[ny][nx] !=-1)continue;
			
			if (MAP[ny][nx] > MAP[now.y][now.x]) 
				visited[ny][nx] = visited[now.y][now.x] + abs(MAP[ny][nx] - MAP[now.y][now.x]) * 2;
			if (MAP[ny][nx] == MAP[now.y][now.x])
				visited[ny][nx] = visited[now.y][now.x] + 1;
			if (MAP[ny][nx] < MAP[now.y][now.x]) visited[ny][nx] = visited[now.y][now.x];
			pq.push({ ny,nx });
;		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << visited[i][j] << " ";
		}cout << '\n';
	}
}


int main() {
	//reset

	//input
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> MAP[i][j];
			visited[i][j] = -1;
		}
	}

	for (int i = 0; i < M; i++) {
		Ternel now;
		cin >> now.sy >> now.sx >> now.ey >> now.ex;
		ter[i] = now;
	}
	cin >> pee;

	//solve
	bfs(1, 1);

	//output


}
