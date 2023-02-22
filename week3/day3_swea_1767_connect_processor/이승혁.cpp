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


int MAP[12][12],coremap[12][12], N, ans,sum;
int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };
struct Coord { int y, x; };
vector<Coord> CORE;

// 전역변수 초기화
void reset() {
	// 기본 MAP
	memset(MAP, 0, sizeof(MAP));
	// 코어 연결 상태 맵
	memset(MAP, 0, sizeof(coremap));
	ans = -21e8;
	sum = 0;
	CORE.clear();
}

// MAP 정보 입력
void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 1) {
				if (i > 0&& i <N && j > 0 && j < N ) {
					CORE.push_back({ i,j });
				}
			}
		}
	}
	copy(&MAP[0][0], &MAP[0][0] + N * N, &coremap[0][0]);
	for (int i = 0; i < CORE.size(); i++) {
		Coord now = CORE[i];
		cout << now.y << " " << now.x << '\n';
	}
}

// 현재 코어가 d 방향으로 끝까지 갈 수 있는가 ?
bool isValid(int idx, int d) {
	Coord core = CORE[idx];
	int en;
	if (d == 0) en = core.y;
	else if (d == 1) en = N - 1 - core.y;
	else if (d == 2) en = core.x;
	else en = N - 1 - core.x;

	// 현재 코어의 좌표부터 끝까지 가보기
	// 상
	for (int i = 0; i < en; i++) {
		int ny = core.y + ydir[d];
		int nx = core.x + xdir[d];

		if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
		// 만약 끝까지 갔다면
		if (ny == 0 || ny == N - 1 || nx == 0 || nx == N - 1) return true;
		// 중간에 코어/선 만난다면 이 방향으로는 갈 수 없다.
		if (coremap[ny][nx] == 1)return false;
	}

}

void connect(int idx, int d) {

}

// CORE 끝까지 연결
void dfs(int level) {
	
	// 기저조건
	// 모든 코어를 확인 해봤을 때, sum이 ans보다 크다면 교체
	if (level == CORE.size()) {
		max(ans, sum);
		sum = 0;
		copy(&MAP[0][0], &MAP[0][0] + N * N, &coremap[0][0]);
		return;
	}

	// 재귀 구성
	// 4방향 확인
	for (int i = 0; i < 4; i++) {
		int ny = CORE[level].y + ydir[i];
		int nx = CORE[level].x + xdir[i];
		
		if (ny < 0 || nx < 0 || ny >= N || nx >= N)continue;
		// 바로 옆에 코어가 있다면 continue
		if (coremap[ny][nx] == 1) continue;

		// 없으면 연결 확인 , core map 수정
		if (isValid(level, i)) {
			connect(level, i);
		}

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
		// 
		//output
		cout << "#" << tc << " " << ans << '\n';
	}
}
/*
7    
0 0 1 0 0 0 0
0 0 1 0 0 0 0
0 0 0 0 0 1 0
0 0 0 0 0 0 0
1 1 0 1 0 0 0
0 1 0 0 0 0 0
0 0 0 0 0 0 0
*/
