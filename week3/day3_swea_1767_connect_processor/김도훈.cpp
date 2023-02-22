#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// 완전탐색
// 코어를 발견했을 때 가장자리와 연결하지 않거나 상하좌우로 연결하는 경우 존재
// 끝에 있는 코어들은 이미 연결된 상태 -> 경우의 수 생각해주지 않아도된다

// 연결하지 않을때 dfs를 어디 위치에서 넣어줘야될지 시행착오 겪음
// 설계는 어렵지 않았지만 구현에서 시간이 걸린듯

struct Node {
	int y;
	int x;
};

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };


int N;
int MAP[13][13];
vector<Node>v;

int MaxConnect;
int MinLeng = 21e8;

void dfs(int idx, int leng, int connect) {	// leng : 길이의 합 connect : 연결된 코어의 개수
	// dfs 돌릴 때 함수 매개변수를 정할 때 매번 어려운듯....
	if (idx == v.size()) {
		if (connect > MaxConnect) {
			MinLeng = leng;
			MaxConnect = connect;
		}
		else if (connect == MaxConnect) {
			MinLeng = min(MinLeng, leng);
		}
		return;
	}

	for (int i = 0; i < 4; i++) {
		int ny = v[idx].y;
		int nx = v[idx].x;
		int cnt = 0;
		
		while (1) {
			ny += dy[i];
			nx += dx[i];
			cnt++;
			if (MAP[ny][nx] == 1 || MAP[ny][nx] == 2) {	// 코어가 있거나 이미 전선이 있는 경우
				cnt = 0;
				break;
			}
			if (MAP[ny][nx] == 0 && (nx == 0 || ny == 0 || nx == N - 1 || ny == N - 1))
				break;
		}
		if (cnt != 0) {
			ny = v[idx].y;
			nx = v[idx].x;
			while (1) {
				ny += dy[i];
				nx += dx[i];
				if (nx<0 || ny<0 || nx>N - 1 || ny>N - 1)
					break;
				MAP[ny][nx] = 2;	// 전선이 배치되었음을 나타내어준다
			}
			dfs(idx + 1, leng + cnt, connect + 1);
			ny = v[idx].y;
			nx = v[idx].x;
			while (1) {
				ny += dy[i];
				nx += dx[i];
				if (nx < 0 || ny < 0 || nx > N - 1 || ny > N - 1)
					break;
				MAP[ny][nx] = 0;
			}

		}
		
	}
	dfs(idx + 1, leng, connect);
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;

		v.clear();
		MaxConnect = 0;
		MinLeng = 21e8;


		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> MAP[i][j];

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (MAP[i][j] == 1) {
					if (i == 0 || i == N - 1 || j == 0 || j == N - 1) continue;
					v.push_back({ i, j });
				}
			}
		}
		dfs(0, 0, 0);
		cout << "#" << tc << " " << MinLeng << '\n';
	}

}