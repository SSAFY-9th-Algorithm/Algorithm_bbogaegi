#include <iostream>
#include <vector>
using namespace std;

int n, m, r, c, l;
int map[50][50];

int dir[4][2] = {
	-1, 0,
	1,0,
	0, -1,
	0, 1
};

vector<vector<int>> xdir = { {0,0,-1,1},{0,0},{-1,1},{0,1},{0,1}, {0,-1},{0,-1} };
vector<vector<int>> ydir = { {-1,1,0,0},{-1,1}, {0,0},{-1,0}, {1,0}, {1,0},{-1,0} };

int cnt = 0;
void dfs(int level, int y, int x, int t, int space) {
	if (level == l) {
		return;
	}

	vector<int> yd = ydir[t - 1];
	vector<int> xd = xdir[t - 1];
	for (int n = 0; n < xd.size(); n++) {
		int ny = y + yd[n];
		int nx = x + xd[n];

		if (ny < 0 || nx < 0 || ny >= n || nx >= m)
			continue;

		if (map[ny][nx] == 0)
			continue;


			
	}
	
}

int main() {
	int t;
	cin >> t;
	
	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> m >> r >> c >> l;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> map[i][j];
			}
		}
		
		cnt = 1;
		dfs(0, r, c, map[r][c], cnt);

		cout << "#" << tc << " " << ans << endl;
	}

}
