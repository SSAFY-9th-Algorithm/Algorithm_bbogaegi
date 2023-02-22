// 각 코어 좌표에서 갈 수 있는 방향 확인
// -> 인접한 코어가 있는가? -> 있으면 못감
// -> 없으면 없는 방향으로 상은 0, 하는 N-1 ,좌 0, 우 N-1까지 끝까지 가본다
// 끝까지 가다가, 끝이 아닌데 1을 발견하면 연결 못하는 것, 리턴
// 끝까지 잘 왔다면 coremap 기록
// 모든 코어를 확인했다면, 되돌아가면서 이전 맵으로 되돌린다

// 재귀 : 상상상상 -> 상상상하 -> 상상상좌 -> 상상상우

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int MAP[12][12], N, Maxcore, ConnectedCore, Minline,line;
int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

struct Coord { int y, x; };
vector<Coord> CORE;

void reset() {
	memset(MAP, 0, sizeof(MAP));
	line = 0;
	ConnectedCore = 0;
	Maxcore = -21e8;
	Minline = 21e8;
	CORE.clear();
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 1) {
				if (i > 0 && i < N-1 && j > 0 && j < N-1) {
					CORE.push_back({ i,j });
				}
			}
		}
	}
}

int toIter(int idx,int d) {
	Coord core = CORE[idx];
	if (d == 0) return core.y;
	else if (d == 1) return N -1 - core.y;
	else if (d == 2) return core.x;
	else return N - 1 - core.x;
}

bool isValid(int idx, int d) {
	Coord core = CORE[idx];
	int en = toIter(idx, d);

	for (int i = 1; i <= en; i++) {
		int ny = core.y + ydir[d]*i;
		int nx = core.x + xdir[d]*i;

		if (MAP[ny][nx] != 0)return false;
		if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
		if (ny == 0 || ny == N - 1 || nx == 0 || nx == N - 1) return true;
	}

}

void connect(int idx, int d, int value) {
	Coord core = CORE[idx];
	int en = toIter(idx, d);

	if (value == 2) line += en;
	else line -= en;

	for (int i = 1; i <= en; i++) {
		int ny = core.y + ydir[d]*i;
		int nx = core.x + xdir[d]*i;
		MAP[ny][nx] = value;
	}

	
}

void dfs(int level) {
	if (level == CORE.size()) {
		if (ConnectedCore > Maxcore) {
			Maxcore = ConnectedCore;
			Minline = line;
		}else if(ConnectedCore==Maxcore){
			Minline = min(Minline, line);
		}
		return;
	}

	for (int i = 0; i < 4; i++) {
		int ny = CORE[level].y + ydir[i];
		int nx = CORE[level].x + xdir[i];

		if (ny < 0 || nx < 0 || ny >= N || nx >= N)continue;
		if (MAP[ny][nx] == 1) continue;

		if (isValid(level, i)) {
			ConnectedCore++;
			connect(level, i, 2);

			dfs(level + 1);

			connect(level, i, 0);
			ConnectedCore--;
		}
		else
			dfs(level + 1);

	}
}


int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// reset
		reset();
		// input 
		input();
		// solve
		dfs(0);
		//output
		cout << "#" << tc << " " << Minline << '\n';
	}
}
