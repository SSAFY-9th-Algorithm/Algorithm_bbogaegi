#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

// 두가지씩 최대가 되는 경우를 찾아야함
// 재귀 (DFS) 활용
// 졸려ㅜㅜㅜㅜㅜㅜㅜㅜㅜㅜㅜ

int N; // 식재료 개수
int synergyMAP[17][17];
int selected[17];
int res;

void dfs(int level, int cnt) {
	// 절반의 식재료를 뽑았다면
	if (cnt == N/2) {
		int A = 0;
		int B = 0;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				// 선택한 식재료를 A에 더하고
				if (selected[i] && selected[j])
					A += synergyMAP[i][j];
				// 나머지 식재료를 B에 더한다
				else if (!selected[i] && !selected[j])
					B += synergyMAP[i][j];
			}
		}
		// 이미 구한 답과 차가 최소가 되는 답을 저장
		res = min(res, abs(A - B));
		return;
	}
	// level이 N보다 크거나 이미 차가 0인 답을 구했다면 종료
	if (level >= N || res == 0)
		return;

	// 선택 안함
	selected[level] = 0;
	dfs(level + 1, cnt);

	// 선택함
	selected[level] = 1;
	dfs(level + 1, cnt + 1);
}

int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		// reset
		res = 21e8;
		memset(synergyMAP, 0, sizeof(synergyMAP));
		memset(selected, 0, sizeof(selected));
		// input
		cin >> N;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> synergyMAP[i][j];
		// solve
		dfs(0, 0);
		// output
		cout << '#' << tc << ' ' << res << '\n';
	}
}
