#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

// 완완
//  '.' : 빈 칸, '#' : 벽, 'O' : 도착지, 'R' : 빨간 구슬, 'B' : 파란 구슬
// while문 종료 조건은 ()안에 넣었더니 안먹어서 한참 시간 들였는데 그냥 밑에서 break로 뺐더니 바로 해결...
// 설계
// #1. 둘다 이동시키고
// #2. 위치가 같으면 더 이동한 애 옮기고
// #3. 그냥 계속 이동하면서 10번안에 들어가면 성공 아니면 실패


struct Node {
	int ry;
	int rx;
	int by;
	int bx;
	int cnt;
};

int N, M;
char MAP[11][11];
int ry, rx, by, bx;

int visited[11][11][11][11];

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

// 벽을 만날때까지 이동시켜 봅시다
void move(int& y, int& x, int& cnt, int& i) {
	while (1)
	{
		if (MAP[y + ydir[i]][x + xdir[i]] == '#' || MAP[y][x] == 'O')
			break;
		y += ydir[i];
		x += xdir[i];
		cnt++;
	}
}

void bfs() {
	queue<Node>q;
	q.push({ ry,rx,by,bx,1 });

	visited[ry][rx][by][bx] = 1;

	while (!q.empty())
	{
		Node now = q.front();
		q.pop();
		// 이동 횟수가 10을 넘어가면 실패!
		if (now.cnt > 10)
			break;
		for (int i = 0; i < 4; i++) {
			int nyr = now.ry, nxr = now.rx, rcnt = 0;
			int nyb = now.by, nxb = now.bx, bcnt = 0;

			move(nyr, nxr, rcnt, i);
			move(nyb, nxb, bcnt, i);

			if (visited[nyr][nxr][nyb][nxb])
				continue;
			// 파란 구슬이 구멍에 빠지면 실패!
			if (MAP[nyb][nxb] == 'O') 
				continue;
			// 빨간 구슬이 구멍에 빠지면 성공
			if (MAP[nyr][nxr] == 'O') {
				cout << now.cnt;
				return;
			}
			// 두 구슬은 같은 위치에 있을 수 없다
			if (nyr == nyb && nxb == nxr) {
				// 이동 횟수가 많은 구슬 한칸 뒤로 이동!
				if (rcnt > bcnt) {
					nyr -= ydir[i];
					nxr -= xdir[i];
				}
				else {
					nyb -= ydir[i];
					nxb -= xdir[i];
				}
			}

			visited[nyr][nxr][nyb][nxb] = 1;
			q.push({ nyr,nxr,nyb,nxb,now.cnt + 1 });
		}
	}
	cout << -1;
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 'R')
				ry = i, rx = j;
			if (MAP[i][j] == 'B')
				by = i, bx = j;
		}
	}
	bfs();

	return 0;
}
