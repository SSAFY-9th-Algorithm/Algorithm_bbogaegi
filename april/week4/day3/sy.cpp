#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
using namespace std;

// 설계
// 1. dfs로 뽑을 수 있는 모든 조합을 뽑고 -> 완전 탐색 같아서 dfs 사용
// 2. 실제 이닝을 진행하며 점수 계산 -> 시뮬
// 3. 점수가 높으면 갱신

int N;
int RES[51][10];
int used[10];
int ord[10];
int ans;

void input() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 1; j <= 9; j++) {
			scanf("%d", &RES[i][j]);	
		}
	}
}

void game() {
	int score = 0;
	int pos[3] = { 0, }; // 0 : 1루 1 : 2루 2: 3루
	int ep = 1, out = 0;
	for (int i = 0; i < N; i++) {
		while(1) {
			switch (RES[i][ord[ep]])
			{
			case 1:
				score += pos[2];
				pos[2] = 0;
				if (pos[1]) {
					pos[2] = 1;
					pos[1] = 0;
				}
				if (pos[0]) {
					pos[1] = 1;
					pos[0] = 0;
				}
				pos[0] = 1;
				break;
			case 2:
				score += (pos[2] + pos[1]);
				pos[2] = 0;
				pos[1] = 0;
				if (pos[0]) {
					pos[2] = 1;
					pos[0] = 0;
				}
				pos[1] = 1;
				break;
			case 3:
				score += (pos[0] + pos[1] + pos[2]);
				pos[0] = 0;
				pos[1] = 0;
				pos[2] = 0;
				pos[2] = 1;
				break;
			case 4:
				score += (pos[0] + pos[1] + pos[2] + 1);
				pos[0] = 0;
				pos[1] = 0;
				pos[2] = 0;
				break;
			default:
				out++;
				break;
			}
			ep++;
			if (ep > 9) ep = 1;
			if (out == 3) {
				out = 0;
				memset(pos, 0, sizeof(pos));
				break;
			}
		}
	}
	if (score > ans)
		ans = score;
}

void dfs(int now) {
	// 기저조건 -> 9번 타자까지 순서가 정해지면 종료 
	// -> 그래서 now가 10일때
	if (now >= 10) {
		game();
		return;
	}
	// 재귀 구성 -> 1~9번 타자를 고른다
	for (int i = 1; i <= 9; i++) {
		if (used[i])
			continue;
		// i번 타자를 골랐다
		used[i] = 1;
		ord[i] = now;
		dfs(now + 1);
		used[i] = 0;
	}
}

void solve() {
	// 4번 타자는 이미 골랐다
	used[4] = 1;
	// 4번 타자는 1
	ord[4] = 1;
	dfs(2);
	printf("%d\n", ans);
}

int main() {
	//freopen("input.txt", "r", stdin);
	input();
	solve();

	return 0;
}
