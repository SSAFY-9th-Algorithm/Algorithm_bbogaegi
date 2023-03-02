## 컨디션 난조
## 이전에 풀던것에서 업그레이드 못함

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct coord {
	int y, x,value;
	bool cmp(coord next) const {
		if (value < next.value) {
			return true;
		}
		if (value > next.value)
			return false;
		return false;

	}
};

int N, M;
int MAP[50][50];
int visited[50][50];
int ty, tx;
int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };


void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 3) {
				ty = i;
				tx = j;
			}
		}
	}
}


bool bfs(int sy, int sx) {

	queue<coord> q;
	q.push({ sy,sx,1});

	while (!q.empty()) {
		coord now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
			if (visited[ny][nx] == 1)continue;
			
			if (MAP[ny][nx] == 1) {
				visited[ny][nx] = 1;
				q.push({ ny,nx });
			}
			if (MAP[ny][nx] == 3)
			{
				cout << visited[now.y][now.x];
				return true;
			}
		}

	}
	return false;
	
	
}

int main() {
	input();
	visited[N - 1][0] = 1;
	if(bfs(N-1,0)==true)return 0;
	else {

		for (int i = N - 1; i >= 0; i--) {
			for (int j = 0; j < M; j++) {
				if (MAP[i][j] == 1 && visited[i][j] == 0) {
					int fi = 0;
					// 4방향 1 있으면 그대로 사용
					for (int d = 0; d < 4; d++) {
						int ny = i + ydir[d];
						int nx = j + xdir[d];

						if (ny < 0 || nx < 0 || ny >= N || nx >= M)continue;
						// 주변에 1이 있고, 이미 값을 가지고 있다면
						if (MAP[ny][nx] == 1 && visited[ny][nx] != 0) {
							visited[i][j] = visited[ny][nx];
							fi = 1;
						}

					}
					if (fi == 0) {
						// i+1부터 N-1까지 1찾기
						int cnt = 0;
						for (int k = i + 1; k < N; k++) {
							cnt++;
							if (MAP[k][j] == 1 || MAP[k][j] == 2)
							{
								visited[i][j] = cnt;
								break;
							}

						}
					}
				}

			}

		}


		int ans = 21e8;
		for (int row = ty; row < N - 1; row++) {
			if (ans > visited[row][tx] && visited[row][tx] != 0) {
				ans = visited[row][tx];
				break;
			}
		}
		for (int row = ty; row >=0 ; row--) {
			if (ans > visited[row][tx] && visited[row][tx] != 0) {
				ans = visited[row][tx];
				break;
			}
		}
		if (tx + 1 < N && visited[ty][tx + 1] != 0)
			if (ans > visited[ty][tx + 1])
				ans = visited[ty][tx + 1];

		if (tx - 1 >= 0 && visited[ty][tx - 1] != 0)
			if (ans > visited[ty][tx - 1])ans = visited[ty][tx - 1];

		cout << ans;
	}

}
