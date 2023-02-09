#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int y;
	int x;
};

int N, M;
int MAP[501][501];
int visited[501][501];
int day, cnt;
int DAT[1001];

void bfs(int y, int x) {
	queue<Node> q;
	q.push({ y, x });

	visited[y][x] = 1;

	int ydir[4] = { -1,1,0,0 };
	int xdir[4] = { 0,0,-1,1 };

	while (!q.empty())
	{
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (nx < 0 || ny < 0 || nx >= M || ny >= N)
				continue;
			if (visited[ny][nx] > 0)
				continue;
			if (MAP[ny][nx] == 0) // 비옥함이 0인경우 통과
				continue;

			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny, nx });
		}
	}

	int end_day; //마지막 피어있는 날
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			end_day = visited[i][j] + MAP[i][j] - 1; // 마지막 피어있는 날
			for (int k = 1; k < 1000; k++) { // k = day
				// 꽃이 핀 날이 k 이전이고 지는 날이 k이후라면 모두 피어있는 꽃의 개수
				if (visited[i][j] > 0 && visited[i][j] <= k && end_day >= k) 
					DAT[k]++;
			}
		}
	}
}


int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			cin >> MAP[i][j];
	}
	int sy, sx;
	cin >> sy >> sx;
	bfs(sy, sx);
	
	// 가장 많이 피어있는 날 구함
	int MAX = -21e8;
	for (int i = 1; i <= 1000; i++) {
		if (DAT[i] > MAX) {
			MAX = DAT[i];
			day = i;
		}
	}
	
	cout << day << "일" << '\n';
	cout << MAX << "개" << '\n';
	return 0;
}
