#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
// 북 동 남 서
int ydir[] = { -1,0,1,0 };
int xdir[] = { 0,1,0,-1 };

struct Node {
	int y, x;
};

int N, M;
int MAP[55][55];
int ry, rx, dir;
int visited[55][55];
int cnt;
int dirRotate[] = { 3,0,1,2 };

void solve(int y, int x) {
	queue<Node> q;
	while (true) {
		int de = 1;
		// 현재 칸이 아직 청소되지 않았다면 
		// 현재 칸을 청소하자
		if (!MAP[y][x]) {
			MAP[y][x] = 2;
			cnt++;
		}
		// 주변 4칸 확인
		q = queue<Node>();
		memset(visited, 0, sizeof(visited));
		visited[y][x] = 1;
		for (int i = 0; i < 4; i++) {
			int ny = y + ydir[i];
			int nx = x + xdir[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= M)
				continue;
			if (visited[ny][nx])
				continue;
			if (MAP[ny][nx])
				continue;
			q.push({ ny, nx });
		}
		// 주변 4칸중 청소되지 않은 빈칸이 없으면
		// 방향을 유지한 채로 한칸 후진하고 반복
		if (q.empty()) {
			y -= ydir[dir];
			x -= xdir[dir];
			if (MAP[y][x] == 1)
				break;
		}
		// 주변 4칸 중 청소지 않은 빈칸이 있으면
		// 반시계방향으로 90도 회전
		// 바라보는 방향 기준 앞쪽이 청소되지 않은 빈칸이면 한칸 전진
		else {
			dir = dirRotate[dir];
			if (MAP[y + ydir[dir]][x + xdir[dir]] == 0) {
				y += ydir[dir];
				x += xdir[dir];
			}
		}
	}
}

int main() {
	fastIO;

	cin >> N >> M;
	cin >> ry >> rx >> dir;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> MAP[i][j];

	solve(ry, rx);
	cout << cnt;
	return 0;
}
