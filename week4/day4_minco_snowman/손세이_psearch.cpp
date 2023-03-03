#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

// 옆반 승욱이한테 물어봤더니 두가지 방법을 줌
// 1. dijkstra -> 올림
// 2. parametic search -> 현재 코드

int N, M;
int MAP[51][51];
int ans;
int sy, sx, dy, dx;

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

bool outRange(int y, int x) {
	return y < 0 || x < 0 || y >= N || x >= M;
}
// 이 limit으로 갈 수있나 탐색을 해보아요
bool bfs(int limit) {
	queue<pair<int, int>>q;
	q.push({ sy, sx });

	int visited[51][51] = { 0, };
	visited[sy][sx] = 1;

	while (!q.empty())
	{
		auto now = q.front();
		q.pop();
		// 위로 갈때도 0인 지점부터는 올라갈 수 없고 좌우도 0이면 갈 수 없으니까 통과
		if (MAP[now.first][now.second] == 0) 
			continue;
		
		// 상하 이동
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j <= limit; j++) { // y축으로는 limit만큼 올라갈 수 있기때문에 거기까지 다 q에 담아서 탐색
				int ny = now.first + ydir[i] * j;
				int nx = now.second + xdir[i] * j;

				if (outRange(ny, nx))
					continue;
				if (visited[ny][nx])
					continue;
				if (j == limit && MAP[ny][nx] == 0) // limit 만큼 올라 갔는데 거기가 땅이 아니면 못감
					continue;

				visited[ny][nx] = 1;
				q.push({ ny, nx });
			}
		}
		// 좌우 이동
		for (int i = 2; i < 4; i++) {
			int ny = now.first + ydir[i];
			int nx = now.second + xdir[i];

			if (outRange(ny, nx))
				continue;
			if (visited[ny][nx])
				continue;
			if (MAP[ny][nx] == 0) // 땅이 아니면 못감
				continue;

			visited[ny][nx] = 1;
			q.push({ ny, nx });
		}
	}
	// 내 목적지를 방문했다면 이 리밋으로 갈 수 있다
	if (visited[dy][dx]) return true; 
	return false;
}
// 가장 작은 limit을 찾을 거에요!
void psearch() {
	int left = 0;
	int right = abs(sy-dy); // 어차피 이 값을 넘어가면 그냥 이값이 답이기 때문에 여기까지 확인

	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (bfs(mid)) { // 중간 값이 된다? 이 limit으로 갈 수있다면
			ans = mid; // 그 값을 저장하고
			right = mid - 1; // 최대치를 낮춘다
		}
		else
			left = mid + 1; // 아니면 최저치를 
	}
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 2)
				sy = i, sx = j;
			if (MAP[i][j] == 3)
				dy = i, dx = j;
		}

	psearch();

	cout << ans;
	return 0;
}
