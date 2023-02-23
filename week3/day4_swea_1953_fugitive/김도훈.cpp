#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

// 현재 위치에 있는 파이프의 종류와 파이프 기준으로 상하좌우 올 수 있는 파이프의 종류가 다달라서 고려해줘야할 조건이 많다고 생각되어
// 이 부분에서 시간이 걸림
// 결국 if문으로 하나하나 다 작성 해줬다는 ...분명히 방법이 있을텐데 일단 풀자라는 마인드
// 이것만 해결하면 단순 flood fill문제

struct Edge {
	int y;
	int x;
};

int N, M, R, C, L;
int MAP[50][50];
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
//int a;
int cnt;

bool check(int y, int x, int a) {	// 이 부분을 어떻게 해결할까 고민하다
									// 그냥 하나하나 다 봐줘서 판단하자해서 일단 다썼음...
		
	int ny = y + dy[a];
	int nx = x + dx[a];

	if (MAP[y][x] == 1) {
		if (a == 0) {
			if (MAP[ny][nx] == 1 || MAP[ny][nx] == 2 || MAP[ny][nx] == 5 || MAP[ny][nx] == 6) {
				return true;
			}
			return false;
		}
		if (a == 1) {
			if (MAP[ny][nx] == 1 || MAP[ny][nx] == 2 || MAP[ny][nx] == 4 || MAP[ny][nx] == 7) {
				return true;
			}
			return false;
		}
		if (a == 2) {
			if (MAP[ny][nx] == 1 || MAP[ny][nx] == 3 || MAP[ny][nx] == 4 || MAP[ny][nx] == 5) {
				return true;
			}
			return false;
		}
		if (a == 3) {
			if (MAP[ny][nx] == 1 || MAP[ny][nx] == 3 || MAP[ny][nx] == 6 || MAP[ny][nx] == 7) {
				return true;
			}
			return false;
		}
	}
	if (MAP[y][x] == 2) {
		if (a == 0) {
			if (MAP[ny][nx] == 1 || MAP[ny][nx] == 2 || MAP[ny][nx] == 5 || MAP[ny][nx] == 6) {
				return true;
			}
			return false;
		}
		if (a == 1) {
			if (MAP[ny][nx] == 1 || MAP[ny][nx] == 2 || MAP[ny][nx] == 4 || MAP[ny][nx] == 7) {
				return true;
			}
			return false;
		}
		if (a == 2) {
			return false;
		}
		if (a == 3) {
			return false;
		}
	}
	if (MAP[y][x] == 3) {
		if (a == 0) {
			return false;
		}
		if (a == 1) {
			return false;
		}
		if (a == 2) {
			if (MAP[ny][nx] == 1 || MAP[ny][nx] == 3 || MAP[ny][nx] == 4 || MAP[ny][nx] == 5) {
				return true;
			}
			return false;
		}
		if (a == 3) {
			if (MAP[ny][nx] == 1 || MAP[ny][nx] == 3 || MAP[ny][nx] == 6 || MAP[ny][nx] == 7) {
				return true;
			}
			return false;
		}
	}
	if (MAP[y][x] == 4) {
		if (a == 0) {
			if (MAP[ny][nx] == 1 || MAP[ny][nx] == 2 || MAP[ny][nx] == 5 || MAP[ny][nx] == 6) {
				return true;
			}
			return false;
		}
		if (a == 1) {
			return false;
		}
		if (a == 2) {
			return false;
		}
		if (a == 3) {
			if (MAP[ny][nx] == 1 || MAP[ny][nx] == 3 || MAP[ny][nx] == 6 || MAP[ny][nx] == 7) {
				return true;
			}
			return false;
		}
	}
	if (MAP[y][x] == 5) {
		if (a == 0) {
			return false;
		}
		if (a == 1) {
			if (MAP[ny][nx] == 1 || MAP[ny][nx] == 2 || MAP[ny][nx] == 4 || MAP[ny][nx] == 7) {
				return true;
			}
			return false;
		}
		if (a == 2) {
			return false;
		}
		if (a == 3) {
			if (MAP[ny][nx] == 1 || MAP[ny][nx] == 3 || MAP[ny][nx] == 6 || MAP[ny][nx] == 7) {
				return true;
			}
			return false;
		}
	}
	if (MAP[y][x] == 6) {
		if (a == 0) {
			return false;
		}
		if (a == 1) {
			if (MAP[ny][nx] == 1 || MAP[ny][nx] == 2 || MAP[ny][nx] == 4 || MAP[ny][nx] == 7) {
				return true;
			}
			return false;
		}
		if (a == 2) {
			if (MAP[ny][nx] == 1 || MAP[ny][nx] == 3 || MAP[ny][nx] == 4 || MAP[ny][nx] == 5) {
				return true;
			}
			return false;
		}
		if (a == 3) {
			return false;
		}
	}
	if (MAP[y][x] == 7) {
		if (a == 0) {
			if (MAP[ny][nx] == 1 || MAP[ny][nx] == 2 || MAP[ny][nx] == 5 || MAP[ny][nx] == 6) {
				return true;
			}
			return false;
		}
		if (a == 1) {
			return false;
		}
		if (a == 2) {
			if (MAP[ny][nx] == 1 || MAP[ny][nx] == 3 || MAP[ny][nx] == 4 || MAP[ny][nx] == 5) {
				return true;
			}
			return false;
		}
		if (a == 3) {
			return false;
		}
	}
}

void bfs(int y, int x) {
	queue<Edge>q;
	q.push({ y, x });
	int visited[50][50] = { 0, };
	visited[y][x] = 1;
	
	int dy[4] = { -1, 1, 0, 0 };
	int dx[4] = { 0, 0, -1, 1 };

	while (!q.empty()) {
		Edge now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= M)
				continue;
			if (visited[ny][nx] != 0)
				continue;
			if (MAP[ny][nx] == 0)
				continue;
			if (!check(now.y, now.x, i))
				continue;
			visited[ny][nx] =  visited[now.y][now.x] + 1;
			// 연결되서 갈 수 있는 길만 flood fill로 채워진다
			// 연결안되서 갈 수 없거나 파이프가 없는 칸은 모두 0이다
			q.push({ ny, nx });
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (visited[i][j] <= L && visited[i][j]>0)
			// flood fill로 채워진 결과를 보고 입력한 시간L 보다 작거나 같은 칸에는
			// 탈주범이 위치할 수 있다
				cnt++;
		}
	}
	/*cout << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << visited[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/
	//cout << cnt;

}



int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {

		cnt = 0;
		memset(MAP, 0, sizeof(MAP));

		cin >> N >> M >> R >> C >> L;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cin >> MAP[i][j];
			}
		}
		bfs(R, C);
		cout << '#' << tc << ' ' << cnt << endl;
	}
}