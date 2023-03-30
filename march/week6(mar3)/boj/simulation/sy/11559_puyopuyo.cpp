#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

// . : 빈 공간
// R은 빨강, G는 초록, B는 파랑, P는 보라, Y는 노랑
int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

struct Node {
	int y, x;
};

const int N = 12, M = 6;
string MAP[12];
int visited[12][6];
int res;

// 중력 구현
void gravity() {
	for (int j = 0; j < M; j++) {
		int h = N - 1;
		for (int i = N - 1; i >= 0; i--) {
			if (MAP[i][j] != '.') {
				char tmp = MAP[i][j];
				MAP[i][j] = '.';
				MAP[h][j] = tmp;
				h--;
			}

		}
	}
}

// 터트리자
void pang(int y, int x, char s) {
	queue<Node> q;
	q.push({ y, x });

	int visit[N][M] = { 0, };
	visit[y][x] = 1;

	MAP[y][x] = '.';

	while (!q.empty())
	{
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= M)
				continue;
			if (visit[ny][nx])
				continue;
			if (MAP[ny][nx] != s)
				continue;

			MAP[ny][nx] = '.';
			visit[ny][nx] = 1;
			q.push({ ny, nx });
		}
	}
}
// 연결된 개수를 확인하자
bool bfs(int y, int x, char s) {
	queue<Node> q;
	q.push({ y, x });

	visited[y][x] = 1;

	int cnt = 1;
	while (!q.empty())
	{
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= M)
				continue;
			if (visited[ny][nx])
				continue;
			if (MAP[ny][nx] != s)
				continue;
			cnt++;
			visited[ny][nx] = 1;
			q.push({ ny, nx });
		}
	}
	int de = 1;
	// 연결된 뿌요뿌요가 4개 이상이면
	if (cnt >= 4) {
		// 터트리고
		pang(y, x, s);
		return true;
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 0; i < 12; i++)
		cin >> MAP[i];
	int chk = 0;
	while (true)
	{
		int de = 1;
		memset(visited, 0, sizeof(visited));
		for (int i = N-1; i >= 0; i--) {
			for (int j = 0; j < M; j++) {
				if (MAP[i][j] >= 'A' && MAP[i][j] <= 'Z' && !visited[i][j]) {
					int flag = bfs(i, j, MAP[i][j]);
					if (flag) chk = 1;
				}
			}
		}
		// 터트린게 한개라도 있다면
		// 연쇄 +1, 중력 작용
		if (chk) {
			res++; 
			gravity();
			chk = 0;
		}
		else
			break;
	}
	
	cout << res;

	return 0;
}
