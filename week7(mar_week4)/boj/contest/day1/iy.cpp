#include <iostream>
using namespace std;

int n, m;
//북, 동, 남, 서
int rob_y, rob_x, rob_d;
int MAP[51][51];
int diry[4] = { -1, 0, 1, 0 };
int dirx[4] = { 0, 1, 0, -1 };
int visited[51][51];
int cnt = 0;

void dfs(int y, int x, int d) {

	int flag = 0;
	for (int i = 0; i < 4; i++) {

		int ny = y + diry[i];
		int nx = x + dirx[i];

		if (MAP[ny][nx] == 0 && visited[ny][nx] == 0) {
			flag = 1;
			break;
		}
	}

	if (flag == 0) {
		int ny = y - diry[d];
		int nx = x - dirx[d];
		
		if (MAP[ny][nx] == 1)
			return;

		if (visited[ny][nx] == 0)
			cnt++;

		visited[ny][nx] = cnt;
		dfs(ny, nx, d);

	}
	else {

		int leftdir = d - 1;
		if (leftdir < 0)
			leftdir = 3;

		int ny = y + diry[leftdir];
		int nx = x + dirx[leftdir];

		while (1) {

			if (MAP[ny][nx] == 0 && visited[ny][nx] == 0)
				break;

			leftdir -= 1;
			if (leftdir < 0)
				leftdir = 3;
			ny = y + diry[leftdir];
			nx = x + dirx[leftdir];

			
		}

		cnt++;
		visited[ny][nx] = cnt;
		dfs(ny, nx, leftdir);

	}

}

int main() {
	cin >> n >> m;
	cin >> rob_y >> rob_x >> rob_d;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> MAP[i][j];
		}
	}

	cnt++;
	visited[rob_y][rob_x] = cnt;
	dfs(rob_y, rob_x, rob_d);

	cout << cnt;
}
