/*
땅의 비옥함에 따라 꽃이 살아 있음
꽃이 피고 적힌 숫자 만큼 살아 있다가 죽음
꽃이 피면 상하좌우 씨앗 퍼짐 (단, 이미 씨앗이 있는 곳 제외)
씨앗 심고 다음날 꽃 핌
=> 효정언니 코드 
*/

#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int y;
	int x;
};

int n, m;
int MAP[500][500];
int fy, fx;
queue<Node> q;
int day;
int maxday, maxcnt;
int visited[500][500]; //씨앗 심어진 곳 확인
// 0: 맨땅, 1:씨앗심어짐, 2~: 개화, -1:꽃이 진 땅
int diry[4] = { -1,1,0,0 };
int dirx[4] = { 0,0,-1,1 };

void check() {
	int cnt = 0;
	//전체 공간에서 피어있는 꽃 개수 계산
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			//꽃이 피어있는 곳만 세기
			if (visited[i][j] > 1)
				cnt++;
		}
	}

	//최대로 개화한 꽃의 개수와 날 갱신
	if (cnt > maxcnt) {
		maxday = day;
		maxcnt = cnt;
	}
}

void blooming() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			//꽃 피우기
			//씨앗 심긴 곳은 그냥 피우면되는데 
			if (visited[i][j] > 0){
				visited[i][j]++;
				// 비옥함이 다했으면 지게 만들기
				if (visited[i][j] - 2 >= MAP[i][j])
					visited[i][j] = -1;
			}
		}
	}
}

void bfs(int y, int x) {
	q.push({ y,x });
	visited[y][x] = 1;

	while (!q.empty()) {
		day++;
		blooming();
		check();

		int qsize = q.size();
		for (int b = 0; b < qsize; b++) {
			Node now = q.front();
			q.pop();

			for (int i = 0; i < 4; i++) {
				int ny = now.y + diry[i];
				int nx = now.x + dirx[i];

				if (ny < 0 || nx < 0 || ny >= n || nx >= m)
					continue;

				if (visited[ny][nx] != 0)
					continue;

				if (MAP[ny][nx] == 0)
					continue;

				visited[ny][nx] = 1;
				q.push({ ny, nx });

			}
		}		
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> MAP[i][j];
		}
	}
	
	cin >> fy >> fx;

	bfs(fy, fx);

	cout << maxday << "일" << endl;
	cout << maxcnt << "개";
}
