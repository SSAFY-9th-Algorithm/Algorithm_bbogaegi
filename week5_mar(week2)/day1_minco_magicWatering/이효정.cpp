#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int N; /// 2 ~ 100

int trees[101];
int odd, even = 0;

void reset() {
	memset(trees, 0, sizeof(trees));
	odd = 0, even = 0;
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> trees[i];
	sort(trees, trees + N);
	for (int i = 0; i < N - 1; i++) {
		int diff = trees[N - 1] - trees[i];
		if (diff > 0) {
			odd += diff % 2; // 결국 홀수의 날짜
			even += diff / 2; // 짝수의 날짜
		}
	}
}

int solution(void) {
	int minAns = 21e8;
	while (true) {
		int oddDay = odd * 2 - 1;
		int evenDay = even * 2;

		int nowAns = 0;
		nowAns = max(oddDay, evenDay);
		if (nowAns > minAns)
			break;
		if (nowAns < minAns)
			minAns = nowAns;
		odd += 2;
		even -= 1;
	}
	return minAns;
}

int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int ans = 0;
		reset();
		input();
		if (odd == 0 && even == 0)
			ans = 0;
		else {
			ans = solution();
		}
		cout << "#" << tc << " " << ans << '\n';
	}
}
