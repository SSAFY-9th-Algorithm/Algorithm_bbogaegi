#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

// 딱히 어려운 점은 없었습니다
// 가장 높은 곳 -> 가장 긴 경로 찾기
// 설계
// #1. 가장 높은 곳의 좌표를 찾는다
// #2. dfs를 돌며 조건에 맞춰 가장 긴 경로를 찾음

int N, K;
int MAP[9][9];
int visited[9][9];
int ans;

// height: 현재 높이, cnt : 등산로 길이 확인용, cut : 깎은 횟수 확인
void dfs(int y, int x, int height, int cnt, int cut) {
	int ydir[4] = { -1,1,0,0 };
	int xdir[4] = { 0,0,-1,1 };

	ans = max(ans, cnt);

	visited[y][x] = 1;

	// dfs 탐색
	for (int i = 0; i < 4; i++) {
		int ny = y + ydir[i];
		int nx = x + xdir[i];
		
		// 범위 체크
		if (ny < 0|| nx < 0 || ny >= N || nx >= N)
			continue;
		// 방문 체크
		if (visited[ny][nx] == 1)
			continue;

		if (MAP[ny][nx] >= height) { // 현재지형과 같거나 높은 지형이면
			if (cut == 0) { //깎은 적이 없다면
				for (int j = 1; j <= K; j++) {
					if (MAP[y][x] > MAP[ny][nx] - j) {
						visited[ny][nx] = 1;
						dfs(ny, nx, MAP[ny][nx] - j, cnt + 1, cut + 1);
						visited[ny][nx] = 0;
					}
				}
			}
		}
		else { // 그냥 갈 수 있는 지형
			visited[ny][nx] = 1;
			dfs(ny, nx, MAP[ny][nx], cnt + 1, cut);
			visited[ny][nx] = 0;
		}
	}
	visited[y][x] = 0;
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		//reset
		N = 0, K = 0;
		memset(MAP, 0, sizeof(MAP));
		memset(visited, 0, sizeof(visited));
		ans = -21e8;
		//input
		cin >> N >> K;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> MAP[i][j];

		//solve
		// max 값 찾기
		int MAX = -21e8;
		for (int i = 0; i < N; i++) 
			for (int j = 0; j < N; j++)
				if (MAP[i][j] > MAX) MAX = MAP[i][j];
		// max값의 좌표에서 dfs 돌리기
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (MAP[i][j] == MAX) dfs(i, j, MAX, 1, 0);

		//output
		cout << "#" << tc << " " << ans << '\n';
	}
}
