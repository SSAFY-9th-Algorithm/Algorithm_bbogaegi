#include <iostream>
#include <queue>
using namespace std;

int N;
int dp[12];

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;

		dp[1] = 1;
		dp[2] = 2;
		dp[3] = 4;
		for (int j = 4; j <= num; j++)
			dp[j] = dp[j - 1] + dp[j - 2] + dp[j - 3];
		cout << dp[num] << '\n';
 	}

	return 0;
}
