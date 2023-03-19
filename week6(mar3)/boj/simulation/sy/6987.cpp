#include <iostream>
using namespace std; 

int arr[6][3];
int ans[4], tmp[6][3];

int case1[] = { 0,0,0,0,0,1,1,1,1,2,2,2,3,3,4 };
int case2[] = { 1,2,3,4,5,2,3,4,5,3,4,5,4,5,5 };

void dfs(int idx, int now) {
	if (ans[idx])
		return;
	// 기저조건 -> 15경기 모두 종료
	if (now == 15) {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 3; j++)
				if (arr[i][j] != tmp[i][j])
					return;
		}
		ans[idx] = 1;
		return;
	}

	int team1 = case1[now];
	int team2 = case2[now];

	// #1. team1이 이겼다!
	tmp[team1][0]++;
	tmp[team2][2]++;
	dfs(idx, now + 1);
	tmp[team1][0]--;
	tmp[team2][2]--;

	// #2. 비겼다!
	tmp[team1][1]++;
	tmp[team2][1]++;
	dfs(idx, now + 1);
	tmp[team1][1]--;
	tmp[team2][1]--;

	// #3. team2가 이겼다!
	tmp[team1][2]++;
	tmp[team2][0]++;
	dfs(idx, now + 1);
	tmp[team1][2]--;
	tmp[team2][0]--;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int tc = 0; tc < 4; tc++) {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 3; j++)
				cin >> arr[i][j];
		}
		dfs(tc, 0);
	}

	for (int i = 0; i < 4; i++)
		cout << ans[i] << ' ';

	return 0;
}
