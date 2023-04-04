#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

struct base {
	int y;
	int x;
	int cq;
};

struct conv { // 편의점
	int y;
	int x;
};
vector<conv>store;



int n, m;
int MAP[15][15];

int t;

int person[30][3];	
int dy[4] = { -1,0,0,1 };
int dx[4] = { 0,-1,1,0 };
vector <base> basecamp;

// 1. 편의점에서 가까운 베이스 캠프 찾기 함수
//	-> 행과 열을 비교해야 한다

// 2. 베이스캠프에서 편의점으로 가는 함수



void goBase(int now) {
	queue<conv> q;
	q.push({ store[now].y, store[now].x });

	int visited[15][15] = { 0 };
	visited[store[now].y][store[now].x] = 1;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << visited[i][j];
		}
		cout << endl;
	}

	while (!q.empty()) {
		int y = q.front().y;
		int x = q.front().x; 
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;

			if (visited[ny][nx]) continue;
			
			if (MAP[ny][nx] == 1) {
				person[now][0] = ny;
				person[now][1] = nx;
				person[now][2] = 1;
				MAP[ny][nx] = 2;
			}

			if (MAP[ny][nx] == 2)continue;

			visited[ny][nx] = 1;
			q.push({ ny,nx });
		}
	}
	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << visited[i][j];
		}
		cout << endl;
	}*/


}




int main() {

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j])
				basecamp.push_back({ i,j,0 });
		}
	}
	for (int i = 0; i < m; i++) {
		int y, x;
		cin >> y >> x; // 좌표가 1부터 시작한다고 가정했기때문에 
		store.push_back({ y - 1, x - 1 }); // 1을 빼준다
	}

	goBase(0);
}
