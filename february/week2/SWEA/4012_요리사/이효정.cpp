#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

/*
	N: 식재료 수 (4 <= N <= 16, 짝수)
	맵 정보(시너지) 1 ~ 20,000

	N / 2의 크기만큼 재료 사용 -> 처음에 2개씩만 사용한다고 생각했었음....
	문제를 끝까지 잘 읽자!

	0 1 | 2 3이 뽑혔다
	2 3 | 0 1과 결과가 같으니 반복되는 작업을 줄여야한다 => 시간초과남..알고싶지 않았음
*/
struct Node {
	int y;
	int x;
};

int mat[16][16];
int visited[16];
int choiceA[8];
int choiceB[8];

int N;
int halfN;
int minDiff = 21e8;

void dfs(int level, int choice) {
	if (level == halfN) {
		int foodA = 0;
		int foodB = 0;
		for (int i = 0; i < N; i++) {
			if (visited[i])
				choiceA[foodA++] = i;
			else
				choiceB[foodB++] = i;
		}
		foodA = 0;
		foodB = 0;
		for (int i = 0; i < halfN - 1; i++) {
			for (int j = i + 1; j < halfN; j++) {
				foodA += mat[choiceA[i]][choiceA[j]];
				foodA += mat[choiceA[j]][choiceA[i]];
				foodB += mat[choiceB[i]][choiceB[j]];
				foodB += mat[choiceB[j]][choiceB[i]];
			}
		}
		minDiff = min(minDiff, abs(foodA - foodB));
		return;
	}
	for (int i = choice; i < N; i++) {
		if (visited[i])
			continue;
		visited[i] = 1;
		dfs(level + 1, i + 1);
		visited[i] = 0;
	}
}

int main(void) {
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// reset
		memset(mat, 0, sizeof(mat));
		memset(visited, 0, sizeof(visited));
		memset(choiceA, 0, sizeof(choiceA));
		memset(choiceB, 0, sizeof(choiceB));
		minDiff = 21e8;

		// input
		cin >> N;
		halfN = N / 2;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				cin >> mat[i][j];
		}
		// solve
		dfs(0, 0);
		// output
		cout << "#" << tc << " " << minDiff << '\n';
	}
}