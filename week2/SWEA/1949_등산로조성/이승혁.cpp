// https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PoOKKAPIDFAUq&categoryId=AV5PoOKKAPIDFAUq&categoryType=CODE&problemTitle=%EB%93%B1%EC%82%B0%EB%A1%9C&orderBy=FIRST_REG_DATETIME&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1
// SWEA 등산로 만들기

// 1. 최대한 긴 등산로
// 2. 가장 높은 봉우리 시작
// 3. 반드시 높은지형 -> 낮은지형 가로 또는 세로 연결
// 3-1. 높이가 같거나, 대각선 방향 연결 불가능
// 4. 딱 한곳을 K만큼 깎을 수 있음
// 5. 가장 높은 봉우리 최대 5개
// 6. 음수도 가능하다.

// 접근
// 1. 가장 높은 봉우리들을 담는다(벡터 / 큐)
// 2. BFS 돌리는??
// 3. DFS ?? 
// 4. 깎을 수 있다. [ny][nx] - K 를 가정하고 ? 
// 5. K-> 를 얼마나 뺄것인가 (ex. 현재 5, K=2, 다음 3 , 그다음 2 일때 1만빼면 4개, 2빼면 못감)

//

#include <iostream>
#include <cstring>
using namespace std;

int N, K;
int MAP[8][8];
int visited[8][8];
int dist = -21e8;

struct Node {
	int x, y;
};

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };
int digged = 0;

void dfs(int y,int x, int level) {
	if (level > dist) {
		dist = level;
	}
	visited[y][x] = 1;

	for (int i = 0; i < 4; i++) {
		int ny = y + ydir[i];
		int nx = x + xdir[i];
		// 갔던 곳 못가게 한다
		if (visited[ny][nx] == 1)continue;

		if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
		// 만약 지금보다 낮은 봉우리면 갈 수 있음

		if (MAP[ny][nx] < MAP[y][x]) {
			visited[ny][nx] = 1;
			dfs(ny, nx, level + 1);
			visited[ny][nx] = 0;
		}

		// 이미 판 적이 있다면 팔 수 없다.
		if (digged == 1)continue;
		// 판 적 없고, 파면 낮아지는 봉우리라면?
		if (MAP[ny][nx] - K < MAP[y][x]) {
			// 파고 간다.
			// 파는데 1~K까지 파는거를 다가본다..?
			for (int dig = 1; dig <= K; dig++) {
				if (MAP[ny][nx] - dig < MAP[y][x]) {
					digged = 1;
					MAP[ny][nx] -= dig;
					visited[ny][nx] = 1;
					dfs(ny, nx, level + 1);
					visited[ny][nx] = 0;
					MAP[ny][nx] += dig;
					digged = 0;
				}
			}
		}

	}

	// 이번 좌표 끝나면 다음 좌표에서는 올 수 있도록
	visited[y][x] = 0;


}

int main() {
	int T;
	int MAX = 0;
	cin >> T;

	for (int tc= 1; tc <= T; tc++) {
		cin >> N>>K; 
		

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> MAP[i][j];
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (MAP[i][j] > MAX)MAX = MAP[i][j];
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (MAP[i][j] == MAX) {
					// 가장 큰 숫자는 dfs돌린다.
					dfs(i, j, 1);
				}
			}
		}

		cout << "#"<<tc<<" "<< dist <<'\n';

		// 초기화 
		memset(MAP, 0, sizeof(MAP));
		dist = -21e8;
		digged = 0;
		MAX = 0;

	}

}

// visited 까먹었었다.
// dfs였는데 bfs였다.

// bfs라고 생각한 이유는 계속해서 타고타고 가기때문에 queue, while, DA 가 떠올랐다.
// dfs가 안될거라고 생각한 이유는 기저조건이 떠오르지 않았다.
// 근데 일단 말로 쓰고 그거에 맞춰 그냥 코드 써보니 통과함
// 어이가 좀 없다.. 내가 푼게 아닌 것 같다.
// 풀이시간 약 30~40분
