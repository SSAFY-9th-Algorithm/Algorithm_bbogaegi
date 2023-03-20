#include <iostream>
using namespace std;

int n, m;
//북, 동, 남, 서
int rob_y, rob_x, rob_d;
int MAP[51][51];
int diry[4] = { -1, 0, 1, 0 };
int dirx[4] = { 0,1,0,-1 };
int visited[51][51];
int cnt = 0;

void dfs(int y, int x, int d) {

	int now = MAP[y][x];

	if (now != 0)
		return;

	if(visited[y][x] == 0 ){
		cnt++;
		visited[y][x] = cnt;
	}

	int flag = 0;
	for (int i = 0; i < 4; i++) {

		int ny = y + diry[i];
		int nx = x + dirx[i];

		if (MAP[ny][nx] == 0 && visited[ny][nx] == 0)
			flag = 1;
	}

	if (flag == 1) {
		int backdir;
		if (d == 0)
			backdir = 2;
		else if (d == 1)
			backdir = 3;
		else if (d == 2)
			backdir = 0;
		else if (d == 3)
			backdir = 2;
		if (MAP[y + diry[backdir]][x + dirx[backdir]] == 1)
			return;

		dfs(y + diry[backdir], x + dirx[backdir], d);
	}
	else {

		int leftdir = d - 1;
		if (leftdir < 0)
			leftdir = 3;

		int ny = y + diry[leftdir];
		int nx = x + dirx[leftdir];

		if (MAP[ny][nx] == 0 && visited[ny][nx] == 0) {
			dfs(ny, nx, leftdir);
		}

		return;

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

	//visited[rob_y][rob_x] = 1;
	dfs(rob_y, rob_x, rob_d);
	
	cout << cnt;
}
