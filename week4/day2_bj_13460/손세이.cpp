#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

// 푸는중
//  '.' : 빈 칸, '#' : 벽, 'O' : 도착지, 'R' : 빨간 구슬, 'B' : 파란 구슬

struct Node {
	int ry;
	int rx;
	int by;
	int bx;
	int cnt;
};

int N, M;
string MAP[11];
int ry, rx, by, bx;

int visited[11][11][11][11];

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

bool outRange(Node tmp) {
	return tmp.ry < 0 || tmp.rx < 0 || tmp.by < 0 || tmp.bx < 0 || tmp.ry >= N || tmp.by >= N || tmp.rx >= M || tmp.bx >= M;
}

void bfs() {
	queue<Node>q;
	q.push({ ry,rx,by,bx,1 });

	visited[ry][rx][by][bx] = 1;

	while (!q.empty())
	{
		Node now = q.front();
		q.pop();

		if (now.cnt > 10)
			break;
		for (int i = 0; i < 4; i++) {
			Node next = now;
			int rcnt = 0, bcnt = 0;
			int flag = 0;
			while (true)
			{
				next.ry += ydir[i];
				next.rx += xdir[i];
				rcnt++; 
				if (outRange(next)) {
					flag = 1;
					break;
				}
				
				if (MAP[next.ry][next.rx] == '#' || MAP[next.ry][next.rx] == 'O')
					break;
			}
			if (flag) continue;
			while (true)
			{
				next.by += ydir[i];
				next.bx += xdir[i];
				bcnt++;
				if (outRange(next)) {
					flag = 1;
					break;
				}
				
				if (MAP[next.by][next.bx] == '#' || MAP[next.by][next.bx] == 'O')
					break;
			}
			if (flag) continue;
			if (visited[next.ry][next.rx][next.by][next.bx])
				continue;

			if (MAP[next.ry][next.rx] == 'O') {
				cout << now.cnt;
				return;
			}

			if (next.bx == next.rx && next.by == next.ry) {
				if (rcnt < bcnt) {
					next.ry -= ydir[i];
					next.rx -= xdir[i];
				}
				else {
					next.by -= ydir[i];
					next.bx -= xdir[i];
				}
			}

			visited[next.ry][next.rx][next.by][next.bx] = 1;
			q.push({ next.ry,next.rx,next.by,next.bx,now.cnt + 1 });
		}
	}
	cout << -1;
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> MAP[i];
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] == 'R')
				ry = i, rx = j;
			if (MAP[i][j] == 'B')
				by = i, bx = j;
		}
	}
	bfs();

	return 0;
}
