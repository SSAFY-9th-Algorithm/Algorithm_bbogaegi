#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

/*
어려웠던 점
#1. 같은 위치에만 있지 않으면 같은 BC를 사용할 수 있다고 생각했음
	누군가 사용중이라면 다른 BC를 쓰거나, 없다면 나눠 써야함
#2. x, y좌표가 원래 사용하던 것과 반대라 헷갈렸음
	-> 입력만 x, y 순서로 받고 처리하는 과정은 원래 하던대로 y, x 순서로 하면 됨
*/

/*
지도 가로, 세로 10
사용자 2 - A (1, 1) B (10, 10)
M : 총 이동시간 20 ~ 100
A : BC개수		1 ~ 8
C : 충전 범위	1 ~ 4
P : 성능		10 ~ 500 짝수
초기 위치(0초부터 충전 가능)
같은 위치에 2개 이상의 BC 설치된 경우는 없음
A, B가 동시에 같은 위치로 이동은 가능
이동 정보
	0 : 이동 X
	1 : 상
	2 : 우
	3 : 하
	4 : 좌
*/

struct BC {
	int idx;
	int P;
	
	bool operator<(BC next) const {
		return P < next.P; // maxHeap 만들기
	}
};

struct Node {
	int y;
	int x;
};

int M; // 총 이동 시간
int A; // BC의 개수
int ydir[5] = { 0, -1, 0, 1, 0 };
int xdir[5] = { 0, 0, 1, 0, -1 };

priority_queue<BC> pq[11][11];
int user1[101];
int user2[101];

void reset() {
	memset(pq, 0, sizeof(pq));
	memset(user1, 0, sizeof(user1));
	memset(user2, 0, sizeof(user2));
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
			pq[i][j].push({ -1, 0 }); // 비어있으면 에러나니 쓸모 없는 값으로 다 채워줌
}

void floodFill(int idx, int sy, int sx, int range, int power) {
	queue<Node> q;
	int visited[15][15] = { 0, };
	int ydir_bc[] = { -1, 1, 0, 0 };
	int xdir_bc[] = { 0, 0, -1, 1 };
	q.push({ sy, sx });
	visited[sy][sx] = 1;
	pq[sy][sx].push({ idx, power });
	while (range) {
		int cursize = q.size();
		for (int z = 0; z < cursize; z++) {
			Node now = q.front();
			q.pop();
			for (int i = 0; i < 4; i++) {
				int ny = now.y + ydir_bc[i];
				int nx = now.x + xdir_bc[i];
				if (ny < 1 || nx < 1 || ny >= 11 || nx >= 11)
					continue;
				if (visited[ny][nx])
					continue;
				visited[ny][nx] = 1;
				q.push({ ny, nx });
				pq[ny][nx].push({ idx, power });
			}
		}
		range--;
	}
}

void input() {
	cin >> M >> A;
	for (int i = 0; i < M; i++)
		cin >> user1[i];
	for (int i = 0; i < M; i++)
		cin >> user2[i];
	for (int i = 0; i < A; i++) {
		int y, x, range, power;
		cin >> x >> y >> range >> power;
		floodFill(i, y, x, range, power);
	}
}

int solution() {
	int total = 0;
	Node u1 = { 1, 1 };
	Node u2 = { 10, 10 };

	total += pq[u1.y][u1.x].top().P;
	total += pq[u2.y][u2.x].top().P;
	for (int i = 1; i <= M; i++) {
		int u1dir = user1[i - 1];
		int u2dir = user2[i - 1];
		u1 = { u1.y + ydir[u1dir], u1.x + xdir[u1dir] };
		u2 = { u2.y + ydir[u2dir], u2.x + xdir[u2dir] };
		if (u1.y == u2.y && u1.x ==  u2.x) { // 두 사용자가 같은 위치에 있다면
			if (pq[u1.y][u1.x].size() < 2) // BC 1개면 나눠씀
				total += pq[u1.y][u1.x].top().P;
			else { // 여러개면 상위 2개 선택
				BC temp = pq[u1.y][u1.x].top();
				pq[u1.y][u1.x].pop();
				total += temp.P;
				total += pq[u1.y][u1.x].top().P;
				pq[u1.y][u1.x].push(temp);
			}
		}
		else { // 다른 위치라면
			BC temp = pq[u1.y][u1.x].top();
			if (temp.idx != -1 && temp.idx == pq[u2.y][u2.x].top().idx) { // 다른 위치지만 같은 걸 쓴다면
				pq[u1.y][u1.x].pop();
				pq[u2.y][u2.x].pop();
				total += temp.P;
				if (pq[u1.y][u1.x].top() < pq[u2.y][u2.x].top())
					total += pq[u2.y][u2.x].top().P;
				else
					total += pq[u1.y][u1.x].top().P;
				pq[u1.y][u1.x].push(temp);
				pq[u2.y][u2.x].push(temp);
			}
			else { // 다른 위치에 있다면
				total += temp.P;
				total += pq[u2.y][u2.x].top().P;
			}
		}
	}
	return total;
}

int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// reset
		reset();
		// input
		input();
		// solve 		// output
		cout << "#" << tc << " " << solution() << '\n';
	}
	return 0;
}
