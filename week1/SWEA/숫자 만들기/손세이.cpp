
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N;
int num[13];
int op[4];
int temp;
int MAX = -21e8;
int MIN = 21e8;
vector<int> used;

// 입력 받는 함수
void INPUT() {
	cin >> N;
	for (int i = 0; i < 4; i++)
		cin >> op[i];
	for (int i = 0; i < N; i++)
		cin >> num[i];
}

// 전역 변수 초기화
void INIT() {
	memset(op, 0, sizeof(op));
	memset(num, 0, sizeof(num));
	temp = 0;
	MAX = -21e8;
	MIN = 21e8;
}

// 선택한 연산자에 따른 계산 결과값을 구하는 함수
int getCalc() {
	int result = num[0];

	for (int i = 0; i < used.size(); i++) {
		if (used[i] == 0) result += num[i + 1];
		if (used[i] == 1) result -= num[i + 1];
		if (used[i] == 2) result *= num[i + 1];
		if (used[i] == 3) result /= num[i + 1];
	}
	return result;
}

// DFS를 통해 모든 경우 탐색
void dfs(int level) {
	//기저 조건: 모든 연산자를 다 확인 했을때
	if (level == N - 1) {
		temp = getCalc();
		if (MIN > temp) MIN = temp;
		if (MAX < temp) MAX = temp;
		return;
	}
	
	for (int i = 0; i < 4; i++) {
		//연산자를 다 사용하면 
		if (op[i] <= 0)
			continue;

		//기록 및 처리
		op[i] -= 1;
		used.push_back(i);

		//재귀 구성
		dfs(level + 1);

		//복구
		op[i] += 1;
		used.pop_back();
	}
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		//reset
		int ans = 0;
		INIT();
		//input
		INPUT();
		//solve
		dfs(0);
		ans = MAX - MIN;
		//output
		cout << "#" << tc << " " << ans << '\n';
	}
	return 0;
}
