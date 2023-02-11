#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int N;
int arr[12];
vector<char> operVec;
int visited[11];
long long _max, _min;
int total;

void dfs(int level) {
	if (level > N - 1) {
		if (_max < total)
			_max = total;
		if (_min > total)
			_min = total;
		return;
	}
	char beforeOper = 0;
	for (int i = 0; i < N - 1; i++) {
		int before = total;
		if (visited[i])
			continue;
		if (operVec[i] == '+')
			total = total + arr[level];
		else if (operVec[i] == '-')
			total = total - arr[level];
		else if (operVec[i] == '*')
			total = total * arr[level];
		else
			total = total / arr[level];
		/*
		 이전에 사용한 연산자와 지금 연산자가 같으면
		 연산 결과 값이 같기 때문에 이럴 경우는 continue
		 */
		if (beforeOper && operVec[i] == beforeOper) {
			total = before;
			continue;
		}
		beforeOper = operVec[i];
		visited[i] = 1;
		dfs(level + 1);
		total = before;
		visited[i] = 0;
	}
}

int main(void) {
	freopen("input.txt", "r", stdin);
	int T;
	char opers[] = "+-*/";
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		operVec.clear();
		_max = -21e8;
		_min = 21e8;
		cin >> N;
		int operators[4];
		for (int i = 0; i < 4; i++) {
			cin >> operators[i];
			for (int j = 0; j < operators[i]; j++)
				operVec.push_back(opers[i]);
		}
		for (int i = 0; i < N; i++)
			cin >> arr[i];
		total = arr[0];
		dfs(1);
		cout << "#" << tc << " " << _max - _min << '\n';
	}
}