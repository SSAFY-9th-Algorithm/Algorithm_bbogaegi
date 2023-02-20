#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int N; // 마을 수 4 <= N <= 8
int people[8]; // 마을 당 유권자수
int mat[8][8]; // MAP
int visited[8];
char path[8];

// A마을로 확정
vector<int> aVillage;
vector<int> bVillage;

int minDiff = 21e8;
int total = 0;

/*
첫번째 접근
모든 마을은 A이거나 B일 수 있다.
DFS로 탐색

A마을, B마을끼리 연결 확인
	-> 유효하다면 minDiff 값 비교
*/

bool dfs_chk() {
	int used[8] = { 0, };
	int aTotal = 0;
	int bTotal = 0;
	if (aVillage.size() == 1) {
		used[aVillage[0]] = 1;
		aTotal = people[aVillage[0]];
	}
	for (int i = 0; i < aVillage.size() - 1; i++) {
		for (int j = i + 1; j < aVillage.size(); j++) {
			if (mat[aVillage[i]][aVillage[j]]) {
				if (!used[aVillage[i]])
					aTotal += people[aVillage[i]];
				if (!used[aVillage[j]])
					aTotal += people[aVillage[j]];
				used[aVillage[i]] = 1;
				used[aVillage[j]] = 1;
			}

		}
	}
	if (bVillage.size() == 1) {
		bTotal = people[bVillage[0]];
		used[bVillage[0]] = 1;
	}
	for (int i = 0; i < bVillage.size() - 1; i++) {
		for (int j = i + 1; j < bVillage.size(); j++) {
			if (mat[bVillage[i]][bVillage[j]]) {
				if (!used[bVillage[i]])
					bTotal += people[bVillage[i]];
				if (!used[bVillage[j]])
					bTotal += people[bVillage[j]];
				used[bVillage[i]] = 1;
				used[bVillage[j]] = 1;
			}
		}
	}

	for (int i = 0; i < N; i++)
		if (!used[i])
			return false;
	minDiff = min(minDiff, abs(aTotal - bTotal));
	return true;
}

void dfs(int level) {
	if (level == N) {
		if (bVillage.size() == 0 || aVillage.size() == 0)
			return;
		dfs_chk();
		return;
	}
	aVillage.push_back(level);
	path[level] = 'A';
	dfs(level + 1);
	path[level] = 0;
	aVillage.pop_back();

	if (level == 0)
		return; // A이거나 B이거나 결과는 똑같을 것
	bVillage.push_back(level);
	path[level] = 'B';
	dfs(level + 1);
	path[level] = 0;
	bVillage.pop_back();
}

int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// reset
		memset(mat, 0, sizeof(mat));
		memset(visited, 0, sizeof(visited));
		memset(people, 0, sizeof(people));
		memset(path, 0, sizeof(path));
		aVillage.clear();
		bVillage.clear();
		minDiff = 21e8;
		total = 0;

		// input
		cin >> N;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> mat[i][j];

		for (int i = 0; i < N; i++) {
			cin >> people[i];
			total += people[i];
		}

		// solve
		dfs(0);
		// output
		cout << "#" << tc << " " << minDiff << '\n';
	}
}
