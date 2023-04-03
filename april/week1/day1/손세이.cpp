#define	_CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <queue>
using namespace std;

struct Node {
	int y, x;
};

// 위 왼 오 아래
int ydir[] = { -1,0,0,1 };
int xdir[] = { 0,-1,1,0 };

int N, M;
int MAP[20][20];
int timeMAP[20][20];
vector<Node> store;
vector<Node> start;

int bfs(int y, int x, int n) {
	queue<Node> q;
	q.push({ y, x });

	int visited[20][20] = { 0, };
	visited[y][x] = 1;

	while (!q.empty())
	{
		Node now = q.front();
		q.pop();

		if (n && MAP[now.y][now.x] == 1) {
			MAP[now.y][now.x] = -n;
			timeMAP[now.y][now.x] = n;
			start.push_back({ now.y, now.x });
			break;
		}

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N)
				continue;
			if (visited[ny][nx])
				continue;
			if (!n && MAP[ny][nx] == MAP[y][x]) {
				timeMAP[ny][nx] = -(MAP[ny][nx] - visited[now.y][now.x]);
				return timeMAP[ny][nx];
			}
			if (!n && timeMAP[ny][nx] && timeMAP[ny][nx] <= visited[now.y][now.x])
				continue;
		
			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny,nx });
		}
	}
	
	return 0;
}

void solve() {
	int t = 0;

	for (int i = 0; i < start.size(); i++) {
		int de = 1;
		Node now = start[i];
		t = max(t, bfs(now.y, now.x, 0));
	}

	//printf("\n");
	//for (int i = 0; i < N; i++) {
	//	for (int j = 0; j < N; j++)
	//		printf("%d ", timeMAP[i][j]);
	//	printf("\n");
	//}
	
	printf("%d\n", t);
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &MAP[i][j]);

	for (int i = 0; i < M; i++) {
		int y, x;
		scanf("%d %d", &y, &x);
		store.push_back({ y-1, x-1 });
	}
	// 가고자하는 편의점과 베이스 캠프 사이의 거리를 구해서
	// 몇번 사람이 어디 베이스 캠프에 갈지 표시해두자
	for (int i = 0; i < store.size(); i++) {
		Node now = store[i];
		bfs(now.y, now.x, i + 1);
		MAP[now.y][now.x] = -(i + 1);
	}
	solve();
	return 0;
}
