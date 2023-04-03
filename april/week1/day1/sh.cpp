#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

struct base { int y, x, cq; };

int MAP[15][15], N, M,t=-1,arrived=0,visited[15][15];
int Cu[30][2];
int Person[30][3];
int ydir[] = { -1,0,0,1 };
int xdir[] = { 0,-1,1,0 };
vector <base> basecamp;

// 편의점 , 베이스캠프 , 사람
// N 번 사람 - > N 번 편의점
// N 번 사람 베이스 캠프 -> N 번 편의점에서 가장 가까운 베이스 캠프

// 지나갈 수 없는 곳 : 이미 사용된 베이스 캠프 , 이미 들어간 편의점

void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j])
				basecamp.push_back({ i,j,0 });
		}
	}

	for (int i = 0; i < M; i++) {
		int y, x;
		cin >> y >> x;
		Cu[i][0] = y-1; Cu[i][1] = x-1;
	}
}

// 편의점 위치 -> 베이스캠프 위치
void moveToBase(int idx) {
	queue<pair<int, int>> q;
	memset(visited, 0, sizeof(visited));
	q.push({ Cu[idx][0],Cu[idx][1] });
	visited[Cu[idx][0]][Cu[idx][1]] = 1;

	while (!q.empty()) {
		int nowy = q.front().first;
		int nowx = q.front().second; q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = nowy + ydir[i];
			int nx = nowx + xdir[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N)continue;
			
			if (visited[ny][nx])continue;
			// 찾았다.
			if (MAP[ny][nx] == 1) {
				Person[idx][0] = ny;
				Person[idx][1] = nx;
				Person[idx][2] = 1; 
				MAP[ny][nx] = 2;
				return;
			}
			if (MAP[ny][nx] == 2)continue;
			visited[ny][nx] = 1;
			q.push({ ny,nx });
		}
	}
}

// 편의점 위치 -> 내위치
void Findnext(int idx) {
	// 1. 편의점에서 내위치로 맵 만든다
	// 2. 끝나면 상 좌 우 하 확인해서 갈 수 있는 곳으로 이동한다.
	queue<pair<int, int>> q;
	memset(visited, 0, sizeof(visited));
	q.push({ Cu[idx][0],Cu[idx][1] });
	visited[Cu[idx][0]][Cu[idx][1]] = 1;

	int ty = Person[idx][0];
	int tx = Person[idx][1];
	int flag = 0;

	while (1) {
		int nowy = q.front().first;
		int nowx = q.front().second; q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = nowy + ydir[i];
			int nx = nowx + xdir[i];
			if (ny < 0 || nx < 0 || nx >= N || ny >= N)continue;
			if (visited[ny][nx])continue;
			// 끝내면 된다.
			if (ny == ty && nx == tx) {
				flag = 1;
				break;
			}
			if (MAP[ny][nx] == 2)continue;
			visited[ny][nx] = visited[nowy][nowx] + 1;
			q.push({ ny,nx });
		}
		if (flag)break;
	}

	for (int i = 0; i < 4; i++) {
		int ny = ty + ydir[i];
		int nx = tx + xdir[i];
		if (ny < 0 || nx < 0 || nx >= N || ny >= N)continue;
		if (visited[ny][nx]) {
			Person[idx][0] = ny;
			Person[idx][1] = nx;
			return;
		}
	}
}

void solution() {
	while (1) {
		t++;
		// 격자에 있는 사람
		for (int i = 0; i < M; i++) {
			if (!Person[i][2])continue;
			// 편의점으로 가장 가까운 방향으로 1 이동
			// 내위치에서 편의점으로 Bfs, 
			Findnext(i);
		}
		// 편의점에 도착한 사람
		for (int i = 0; i < M; i++) {
			// 이미 도착했거나, 출발 안한사람
			if (!Person[i][2])continue; 
			if (Person[i][0] == Cu[i][0] && Person[i][1] == Cu[i][1]) {
				arrived++;
				MAP[Person[i][0]][Person[i][1]] = 2;
				Person[i][2] = 0;
			}
		}

		if (t < M) moveToBase(t); // 0번 ~ M-1번 사람 베이스 캠프 이동

		if (arrived == M)break;
		
	}

}
int main() {
	input();
	solution();
	cout << t + 1;
}
