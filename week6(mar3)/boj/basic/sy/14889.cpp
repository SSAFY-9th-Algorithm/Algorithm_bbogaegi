#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N;
int MAP[21][21];
int used[21];
int ans = 21e8;

void dfs(int now, int cnt) {
	if (cnt == N / 2) {
		int A = 0, B = 0;
		for(int i=0;i<N;i++)
			for (int j = 0; j < N; j++) {
				if (used[i] && used[j])
					A += MAP[i][j];
				if (!used[i] && !used[j])
					B += MAP[i][j];
			}
		ans = min(ans, abs(A - B));
		return;
	}

	if (now == N || ans == 0)
		return;

	used[now] = 1;
	dfs(now + 1, cnt + 1);
	used[now] = 0;

	dfs(now + 1, cnt);
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> MAP[i][j];

	dfs(0, 0);
	cout << ans;
	return 0;
}
