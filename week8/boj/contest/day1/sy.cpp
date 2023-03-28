#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

struct Wood {
	int y, x;
	int age;

	bool operator < (Wood next) const {
		if(age > next.age)
			return true;
		if (age < next.age)
			return false;
		return false;
	}
};

int ydir[] = { -1,-1,-1,0,0,1,1,1 };
int xdir[] = { -1,0,1,-1,1,-1,0,1 };

int MAP[15][15]; // 양분을 저장할 맵
priority_queue<Wood> wood; // 살아있는 나무
int A[15][15]; // 겨울에 추가되는 양분의 양
int N, M, K;
queue<Wood> q; // 죽은 나무
int res;

void input() {
	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
			MAP[i][j] = 5;
		}

	for (int i = 0; i < M; i++) {
		int x, y, z;
		cin >> y >> x >> z;
		wood.push({ y, x, z });
	}
}

void solve() {
	int year = 0;
	queue<Wood> temp;
	while (true) {
		// 봄 -> 자신의 나이만큼 양분을 먹고, 나이가 1 증가
		// 그런데 양분이 부족하면 나무가 죽는다
		while (!wood.empty()) {
			Wood now = wood.top();
			wood.pop();

			int tmp = MAP[now.y][now.x] - now.age;
			// 양분이 부족하면 이 나무는 죽었다!
			if (tmp < 0) {
				q.push(now);
				continue;
			}
			// 양분이 충분하면 양분을 먹고 나무가 자란다!
			MAP[now.y][now.x] = tmp;
			now.age++;
			temp.push(now);
		}
		// 여름 -> 봄에 죽은 나무가 양분으로 바뀐다
		while (!q.empty()) {
			Wood now = q.front();
			q.pop();

			MAP[now.y][now.x] += now.age / 2;
		}

		// 가을 -> 번식하는 나무는 나이가 5의 배수이어야 하며, 
		// 인접한 8개의 칸에 나이가 1인 나무
		while (!temp.empty()) {
			Wood now = temp.front();
			temp.pop();
			wood.push(now);
			// 5의 배수가 아니면 continue
			if (now.age % 5 != 0)
				continue;
			// 8방향 번식
			for (int d = 0; d < 8; d++) {
				int ny = now.y + ydir[d];
				int nx = now.x + xdir[d];

				if (ny < 1 || nx < 1 || ny > N || nx > N)
					continue;

				wood.push({ ny, nx, 1 });
			}
		}
		// 겨울 -> 땅에 양분을 추가
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				MAP[i][j] += A[i][j];

		// 1년이 지났다!
		year++;
		if (year == K)
			break;
	}
	res = wood.size();
}

int main() {
	fastIO;
	input();
	solve();
	cout << res;
	return 0;
}
