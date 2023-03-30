#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

// ���� ��ġ�� �ִ� �������� ������ ������ �������� �����¿� �� �� �ִ� �������� ������ �ٴ޶� ���������� ������ ���ٰ� �����Ǿ�
// �� �κп��� �ð��� �ɸ�
// �ᱹ if������ �ϳ��ϳ� �� �ۼ� ����ٴ� ...�и��� ����� �����ٵ� �ϴ� Ǯ�ڶ�� ���ε�
// �̰͸� �ذ��ϸ� �ܼ� flood fill����

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

bool check(int y, int x, int a) {	// �� �κ��� ��� �ذ��ұ� ����ϴ�
									// �׳� �ϳ��ϳ� �� ���༭ �Ǵ������ؼ� �ϴ� �ٽ���...
		
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
			// ����Ǽ� �� �� �ִ� �游 flood fill�� ä������
			// ����ȵǼ� �� �� ���ų� �������� ���� ĭ�� ��� 0�̴�
			q.push({ ny, nx });
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (visited[i][j] <= L && visited[i][j]>0)
			// flood fill�� ä���� ����� ���� �Է��� �ð�L ���� �۰ų� ���� ĭ����
			// Ż�ֹ��� ��ġ�� �� �ִ�
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