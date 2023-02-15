#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

struct Microbe {
	int y;
	int x;
	int num;
	int dir;
};
struct Pos {
	int y;
	int x;
};

int N, M, K; // 셀 개수, 격리 시간, 미생물 군집 개수

int ydir[4] = { -1, 1, 0, 0 }; // 상하좌우
int xdir[4] = { 0, 0, -1, 1 };

Microbe microbe[1000];

void afterHour() {
	vector<int> pos[100][100];
	for (int i = 0; i < K; i++) {
		int ny = microbe[i].y + ydir[microbe[i].dir];
		int nx = microbe[i].x + xdir[microbe[i].dir];
		if (ny < 0) ny = 0;
		if (nx < 0) nx = 0;
		microbe[i].y = ny;
		microbe[i].x = nx;
		if ((ny == 0 || ny == N - 1) || (nx == 0 || nx == N - 1))
			microbe[i].num /= 2;
		if (microbe[i].dir % 2)
			microbe[i].dir += 1;
		else
			microbe[i].dir -= 1;
		if (microbe[i].num)
			pos[microbe[i].y][microbe[i].x].push_back(i);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (pos[i][j].size() < 1) {
				continue;
			}
			int maxMicro = pos[i][j][0];
			int num = microbe[pos[i][j][0]].num;
			microbe[pos[i][j][0]].num = 0;
			for (int z = 1; z < pos[i][j].size(); z++) {
				num += microbe[pos[i][j][z]].num;
				if (microbe[maxMicro].num < microbe[pos[i][j][z]].num) {
					maxMicro = pos[i][j][z];
				}
				microbe[pos[i][j][z]].num = 0;
			}
			microbe[maxMicro].num = num;
		}
	}
}

int main(void) {
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		memset(microbe, 0, sizeof(microbe));
		cin >> N >> M >> K;
		for (int i = 0; i < K; i++) {
			cin >> microbe[i].y >> microbe[i].x >> microbe[i].num >> microbe[i].dir;
			microbe[i].dir--;
		}
		for (int i = 0; i < M; i++) {
			afterHour();
		}
		int total = 0;
		for (int i = 0; i < K; i++) {
			total += microbe[i].num;
		}
		cout << "#" << tc << " " << total << '\n';
	}
}
