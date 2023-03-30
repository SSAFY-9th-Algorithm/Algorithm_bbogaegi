#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct cctv {
	int y;
	int x;
	int dir;
};

bool cmp(cctv left, cctv right) {
	return left.dir > right.dir;
}

int n, m;
vector<cctv> v;
int cctvCnt, wallCnt;
char MAP[9][9];
int visited[9][9];
//북 동 남 서
int diry[4] = { -1, 0, 1, 0 };
int dirx[4] = { 0, 1, 0, -1 };
int dtype[6][4] = {
	{0, 0, 0, 0},
   {0, 1, 0, 0},
   {0, 1, 0, 1},
   {1, 1, 0, 0},
   {1, 1, 0, 1},
   {1, 1, 1, 1}
};
int tmpVisited[9][9];
int minbehind = 21e8;

void check(cctv tc) {
	int cnt = 0;

	if (tc.dir != 2 && tc.dir != 5) {
	
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				tmpVisited[i][j] = visited[i][j];
			}
		}
	
		for (int t = 0; t < 4; t++) {
			for (int i = 0; i < 4; i++) {
				int tmp = i + t;
				if (tmp >= 4)
					tmp - 4;
				int nowdir = dtype[tc.dir][tmp];
				if (nowdir != 1)
					continue;

				int ny = tc.y + diry[i];
				int nx = tc.x + dirx[i];

				if (ny < 0 || nx < 0 || ny >= n || nx >= m)
					continue;

				if (MAP[ny][nx] == '#')
					continue;

				visited[ny][nx] = 1;
				while (1) {
					ny += diry[i];
					nx += dirx[i];
					if (ny < 0 || nx < 0 || ny >= n || nx >= m)
						break;

					if (MAP[ny][nx] == '#')
						break;

					visited[ny][nx] = 1;
				}
			}

			//개수 세기
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					if (visited[i][j] == 0)
						cnt++;
				}
			}

			if (cnt < minbehind) {
				minbehind = cnt;
				cnt = 0;
			}
			else {
				//복구
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < m; j++) {
						visited[i][j] = tmpVisited[i][j];
					}
				}
			}
		}
	}
	else if (tc.dir == 5) {
		for (int i = 0; i < 4; i++) {
			int nowdir = dtype[tc.dir][i];
			if (nowdir != 1)
				continue;

			int ny = tc.y + diry[i];
			int nx = tc.x + dirx[i];

			if (ny < 0 || nx < 0 || ny >= n || nx >= m)
				continue;

			if (MAP[ny][nx] == '#')
				continue;

			visited[ny][nx] = 1;
			while (1) {
				ny += diry[i];
				nx += dirx[i];
				if (ny < 0 || nx < 0 || ny >= n || nx >= m)
					break;

				if (MAP[ny][nx] == '#')
					break;

				visited[ny][nx] = 1;
			}
		}

		//개수 세기
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (visited[i][j] == 0)
					cnt++;
			}
		}

		if (cnt < minbehind) {
			minbehind = cnt;
			cnt = 0;
		}
		else {
			//복구
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					visited[i][j] = tmpVisited[i][j];
				}
			}
		}
	}
	else if (tc.dir == 2) {
		for (int t = 0; t < 2; t++) {
			int tmpdtype[4] = { 0,1,0,1 };
			if (t == 1) {
				tmpdtype[0] = 1;
				tmpdtype[1] = 0;
				tmpdtype[2] = 1;
				tmpdtype[3] = 0;
			}

			for (int i = 0; i < 4; i++) {
				int nowdir = tmpdtype[i];
				if (nowdir != 1)
					continue;

				int ny = tc.y + diry[i];
				int nx = tc.x + dirx[i];

				if (ny < 0 || nx < 0 || ny >= n || nx >= m)
					continue;

				if (MAP[ny][nx] == '#')
					continue;

				if (MAP[ny][nx] != '0') {

				}

				visited[ny][nx] = 1;
				while (1) {
					ny += diry[i];
					nx += dirx[i];
					if (ny < 0 || nx < 0 || ny >= n || nx >= m)
						break;

					if (MAP[ny][nx] == '#')
						break;

					if (MAP[ny][nx] != '0') {

					}

					visited[ny][nx] = 1;
				}
			}

			//개수 세기
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					if (visited[i][j] == 0)
						cnt++;
				}
			}

			if (cnt < minbehind) {
				minbehind = cnt;
				cnt = 0;
			}
			else {
				//복구
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < m; j++) {
						visited[i][j] = tmpVisited[i][j];
					}
				}
			}
		}
		
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] != '0' || MAP[i][j] != '#') {
				v.push_back({ i, j, MAP[i][j] });
				cctvCnt++;
			}
			if (MAP[i][j] == '#')
				wallCnt++;
		}
	}

	if (cctvCnt == 0) {
		cout << n * m - wallCnt;
		return 0;
	}

	sort(v.begin(), v.end(), cmp);

	for (int i = 0; i < v.size(); i++) {
		cctv target = v[i];
		check(target);
	}

	cout << minbehind;
}
