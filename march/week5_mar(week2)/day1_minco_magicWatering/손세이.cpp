//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

// feat. 득화 교수님
// 날짜 계산기

int N;
int trees[101];
int mxh;

void INIT() {
	memset(trees, 0, sizeof(trees));
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> trees[i];
	}
}

int solve() {
	sort(trees, trees + N);
	mxh = trees[N - 1];
	int day = 21e8;
	
	int odd = 0;
	int even = 0;

	for (int i = 0; i < N - 1; i++) {
		int tmp = mxh - trees[i];
		if (tmp) {
			odd += (tmp % 2);
			even += (tmp / 2);
		}
	}

	if (odd == 0 && even == 0)
		return 0;
	while (true)
	{
		int oday = odd * 2 - 1;
		int eday = even * 2;

		int tmp = 0;
		if (oday > eday)
			tmp = oday;
		else
			tmp = eday;

		if (tmp > day)
			break;

		odd += 2;
		even--;
		day = min(day, tmp);
	}

	return day;
}

int main() {
	//freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// reset
		INIT();
		// input
		input();
		// solve
		int ans = solve();
		// output
		cout << '#' << tc << ' ' << ans << '\n';

		int de = 1;
	}

	return 0;
}
