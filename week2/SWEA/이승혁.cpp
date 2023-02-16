// ### 미해결 문제 ###// ### 미해결 문제 ###// ### 미해결 문제 ###// ### 미해결 문제 ###// ### 미해결 문제 ###
// 접근 방식은 재귀로 4개면 n/2개씩 path -> v.push_back ( [01 02 03 12 13 23] ) 다 담는다
// i= 0 ~ 벡터 사이즈/2까지, i & vsize-i 쌍으로 하면 조합 완성(01,23) ( 02,13) (03,12) 
// 걔들 계산 -> MIN=min(MIN,abs(map[1][0] + map[0][1] - map[2][3] + map[3][2]))
// 6개부터는 3번줄 조합도 포문을 돌려야함.. (1,2,3) (4,5,6) -> 12 13 23 , 45 46 56 이딴식으로 푸는게 맞나 모르겠는데..
// 미생물로 체력 소진.
// ### 미해결 문제 ###// ### 미해결 문제 ###// ### 미해결 문제 ###// ### 미해결 문제 ###// ### 미해결 문제 ###
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n,idx=0;
int path[16],used[16];
int map[16][16];
vector<int> v[100];
int MIN = 21e8;
// N 개 중 N/2 개 고르기
// 여기서 나온 패스 쌍을 벡터에 받아서 0&N, 1&N-1, 2&N-2 순서로 계산하면 됨
void dfs(int level) {
	if (level == n/2) {
		for (int i = 0; i < n / 2; i++) {
			v[idx].push_back(path[i]);
		}idx++;
		return;
	}
	for (int i =level; i <= (n/2)+level; i++) {
		if (used[i] == 1)continue;
		if (level > 0 && i < path[level - 1])continue;
		used[i] = 1;
		path[level] = i;
		dfs(level + 1);
		path[level] = 0;
		used[i] = 0;

			
	}
}

// size N 배열의 시너지 값 구하기..
void calc(int idx1, int idx2) {
	// 2개짜리가 들어오면 01&10, 23&32
	// 3개면 01,02,12 & 10, 20, 21  / 34,35,45, 43,53,54 ...
	int sj1 = 0, sj2 = 0;
	for (int i = 0; i < n / 2 - 1; i++) {
		for (int j = i + 1; j < n / 2; j++) {
			sj1 += map[v[idx1][i]][v[idx1][j]];
			sj1 += map[v[idx1][j]][v[idx1][i]];
			sj2 += map[v[idx2][i]][v[idx2][j]];
			sj2 += map[v[idx2][j]][v[idx2][i]];
		}
	}
	cout << idx1 << ", " << idx2 << MIN << '\n';
	if (abs(sj1 - sj2) < MIN)MIN = abs(sj1 - sj2);
}




int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		//reset
		memset(path, 0, sizeof(path));
		memset(map, 0, sizeof(map));
		memset(used, 0, sizeof(used));
		// input
		cin >> n;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> map[i][j];
			}
		}

		//solve
		dfs(0);
		for (int i = 0; i < 3; i++) {
			calc(i, 6 - i);
		}

		//output
		cout << MIN;
	}
}
/*
1
4
0 5 3 8
4 0 4 1
2 5 0 3
7 2 3 0
*/
