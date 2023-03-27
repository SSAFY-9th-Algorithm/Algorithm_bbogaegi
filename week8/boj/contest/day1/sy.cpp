#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

struct Wood {
	int y, x;
	int age;
	int live;

	bool operator < (Wood next) const {
		return age < next.age;
	}
};

int ydir[] = { -1,-1,-1,0,0,1,1,1 };
int xdir[] = { -1,0,1,-1,1,-1,0,1 };

int MAP[15][15]; // 각 칸에 있는 나무 개수표시
int board[15][15]; // 양분을 저장할 맵
vector<Wood> wood;
int A[15][15]; // 겨울에 추가되는 양분의 양
int N, M, K;
queue<Wood> q;
int res;

void input() {
	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
			board[i][j] = 5;
		}

	for (int i = 0; i < M; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		wood.push_back({ y, x, z, 1 });
		MAP[y][x]++;
	}
}

void grownTree(int i, int y, int x, int age) {
	if (board[y][x] <= 0) return;
	int tmp = board[y][x] - age;
	// 양분을 먹고 나무의 나이 증가!
	if (tmp >= 0) {
		board[y][x] = tmp;
		wood[i].age++;
	}
	// 양분이 부족하면 이 나무는 죽었다!
	else {
		wood[i].live = 0;
		q.push(wood[i]);
		MAP[y][x]--;
	}
}

void solve() {
	int year = 0;
	
	while (true)
	{
		sort(wood.begin(), wood.end());
		// 봄 -> 자신의 나이만큼 양분을 먹고, 나이가 1 증가
		int de = 1;
		for (int i = 0; i < wood.size(); i++) {
			Wood now = wood[i];
			// 죽은 나무면 continue
			if (!now.live) continue;
			// 나무는 양분을 먹고 자란다!
			grownTree(i, now.y, now.x, now.age);
			// 2개 이상의 나무가 한칸에 있다면
			if (MAP[now.y][now.x] >= 2) {
				for (int j = 0; j < wood.size(); j++) {
					if (i == j) continue;
					Wood B = wood[j];
					if (!B.live) continue;
					if (now.y == B.y && now.x == B.x) 
						grownTree(j, B.y, B.x, B.age);
				}
			}
		}
		// 여름 -> 봄에 죽은 나무가 양분으로 바뀐다
		while (!q.empty())
		{
			Wood now = q.front();
			q.pop();

			board[now.y][now.x] += now.age / 2;
		}

		// 가을 -> 번식하는 나무는 나이가 5의 배수이어야 하며, 인접한 8개의 칸에 나이가 1인 나무
		int SIZE = wood.size();
		for (int i = 0; i < SIZE; i++) {
			Wood now = wood[i];
			if (!now.live) 
				continue;
			if (now.age % 5 != 0)
				continue;

			for (int d = 0; d < 8; d++) {
				int ny = now.y + ydir[d];
				int nx = now.x + xdir[d];

				if (ny < 1 || nx < 1 || ny > N || nx > N)
					continue;

				MAP[ny][nx]++;
				wood.push_back({ ny, nx, 1, 1 });
			}
		}
		// 겨울 -> 땅에 양분을 추가
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				board[i][j] += A[i][j];

		// 1년이 지났다!
		year++;
		if (year == K)
			break;
	}
	for (int i = 0; i < wood.size(); i++)
		if (wood[i].live)
			res++;
}

int main() {
	fastIO;
	input();
	solve();
	cout << res;
	return 0;
}
