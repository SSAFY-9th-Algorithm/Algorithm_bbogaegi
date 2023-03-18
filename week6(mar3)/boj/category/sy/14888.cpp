#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

int N;
int num[12];
int op[4]; // + - x /
int MIN = 21e8;
int MAX = -21e8;
int path[12];

int getCalc() {
	int res = num[0];
	for (int i = 0; i < N-1; i++) {
		if (path[i] == 0) res += num[i + 1];
		if (path[i] == 1) res -= num[i + 1];
		if (path[i] == 2) res *= num[i + 1];
		if (path[i] == 3) res /= num[i + 1];
	}
	return res;
}

void dfs(int now) {
	if (now == N - 1) {
		int tmp = getCalc();
		MIN = min(tmp, MIN);
		MAX = max(tmp, MAX);
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (op[i] <= 0)
			continue;

		op[i]--;
		path[now] = i;
		dfs(now + 1);
		op[i]++;
		path[now] = -1;
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> num[i];
	for (int i = 0; i < 4; i++)
		cin >> op[i];
	dfs(0);

	cout << MAX << '\n';
	cout << MIN << '\n';
	return 0;
}
