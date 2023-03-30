#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

int n, m, k;
int MAP[21][21];
struct smell {
	int sNum;
	int k;
};
smell smellMAP[21][21];
int startsharkDir[401];

struct shark {
	int y;
	int x;
	int sNum;
	int sDir;
};
vector<shark>sharkvec;
int diry[4] = { -1, 1, 0, 0 };
int dirx[4] = { 0, 0, -1, 1 };
struct sharkDir {
	int dir[4]; //위, 아래, 좌, 우
};
vector<sharkDir> sharkdirvec[401];
int sharkCnt;

void input() {
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] != 0) {
				smellMAP[i][j] = { MAP[i][j], k };
				sharkvec.push_back({ i, j, MAP[i][j] });
				sharkCnt++;
			}
		}
	}

	for (int i = 0; i < m; i++) {
		int dir;
		cin >> dir;
		for (int j = 0; j < sharkvec.size(); j++) {
			if(sharkvec[j].sNum == i+1)
				sharkvec[j].sDir = dir;
		}
	}

	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < 4; j++) {
			sharkDir sd;
			cin >> sd.dir[0] >> sd.dir[1] >> sd.dir[2] >> sd.dir[3];
			sharkdirvec[i].push_back(sd);
		}
	}

}

int main() {

	input();

	int t = 0;
	while (1) {

		//등호 포함 or 미포함 잘 고려하자!!!
		if (t >= 1000) {
			cout << -1;
			return 0;
		}

		//상어들을 이동시킴.
		for (int q = 0; q < sharkvec.size(); q++) {
			shark now = sharkvec[q];
			if (now.sNum == 0)
				continue;
			sharkDir nowdir = sharkdirvec[now.sNum][now.sDir - 1];
			int ny, nx, ndir;
			int flag = 0;
			for (int d = 0; d < 4; d++) {
				ny = now.y + diry[nowdir.dir[d] - 1];
				nx = now.x + dirx[nowdir.dir[d] - 1];
				ndir = nowdir.dir[d];
				if (ny >= 0 && nx >= 0 && ny < n && nx < n) {
					if (smellMAP[ny][nx].sNum == 0) {
						flag = 1;
						break;
					}
				}
			}

			if (flag != 1) {
				for (int d = 0; d < 4; d++) {
					ny = now.y + diry[nowdir.dir[d] - 1];
					nx = now.x + dirx[nowdir.dir[d] - 1];
					ndir = nowdir.dir[d];
					if (ny >= 0 && nx >= 0 && ny < n && nx < n) {
						if (smellMAP[ny][nx].sNum == now.sNum) {
							flag = 1;
							break;
						}
					}
				}
			}

			sharkvec[q].sDir = ndir;
			sharkvec[q].y = ny;
			sharkvec[q].x = nx;

		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (smellMAP[i][j].sNum == 0)
					continue;
				smellMAP[i][j].k--;
				if (smellMAP[i][j].k == 0) {
					smellMAP[i][j].sNum = 0;
				}
			}
		}

		//없애기
		int cycle = sharkvec.size();
		for (int i = 0; i < cycle; i++) {
			for (int j = i + 1; j < cycle; j++) {
				if (sharkvec[i].sNum == 0 || sharkvec[j].sNum == 0)
					continue;
				if (sharkvec[i].y == sharkvec[j].y && sharkvec[i].x == sharkvec[j].x) {
					if (sharkvec[i].sNum < sharkvec[j].sNum) {
						sharkvec[j].sNum = 0;
						smellMAP[sharkvec[i].y][sharkvec[i].x] = { sharkvec[i].sNum, k };
					}
					else {
						sharkvec[i].sNum = 0;
						smellMAP[sharkvec[j].y][sharkvec[j].x] = { sharkvec[j].sNum, k };
					}
				}
				else {
					smellMAP[sharkvec[i].y][sharkvec[i].x] = { sharkvec[i].sNum, k };
					smellMAP[sharkvec[j].y][sharkvec[j].x] = { sharkvec[j].sNum, k };
				}
			}
		}

		vector<shark>newsharkvec;
		for (int i = 0; i < cycle; i++) {
			shark now = sharkvec.back();
			sharkvec.pop_back();
			if (now.sNum != 0)
				newsharkvec.push_back(now);
		}
		sharkvec.clear();
		sharkvec.resize(newsharkvec.size());
		copy(newsharkvec.begin(), newsharkvec.end(), sharkvec.begin());

		if (sharkvec.size() == 1 && sharkvec[0].sNum == 1)
			break;

		t++;

	}

	cout << t + 1;

}
