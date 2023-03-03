/*
상,하,좌,우 이동해서 보석 먹기
좌,우 -> 땅만 이동
상,하 -> 한 칸 당 게이지 1업. LIMIT넘으면 녹아서 죽.. 땅 밟음 게이지 0 초기화
LIMIT 설정 작을수록 높은 점수 겟.
""보석을 먹기 위한 최소 LIMIT 값 구하기""
*/

#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int y;
	int x;
	int cost;

	bool operator<(Node right) const{
		return cost > right.cost;
	}
};

int n, m;
int snowy, snowx, jewy, jewx;
int MAP[50][50];

int diry[4] = { -1, 1, 0, 0 };
int dirx[4] = { 0,0,-1,1 };

void dijkstra(int sy, int sx) {

	priority_queue<Node> pq;
	pq.push({ sy,sx,0 });

	int dist[50][50] = { 0, };
	int MAX = 21e8;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			dist[i][j] = MAX;

	dist[sy][sx] = 0;

	while (!pq.empty()) {
		Node now = pq.top();
		pq.pop();

		for (int i = 0; i < 4; i++) {
			//상하좌우 나누기
			int flag = 0;
			int ny = now.y + diry[i];
			int nx = now.x + dirx[i];

			while (flag != 1) {
				if (ny < 0 || nx < 0 || ny >= n || nx >= m)
					break;

				Node next;
				if (i == 0 || i == 1) {
					//상하로 이동
					next = { ny, nx, 1 };
				}
				else {
					//좌우로 이동
					next = { ny, nx, 0 };
					if (MAP[next.y][next.x] == 0)
						continue;
				}

				int ncost = dist[now.y][now.x] + next.cost;

				if (dist[next.y][next.x] <= ncost)
					continue;
				dist[next.y][next.x] = ncost;

				pq.push({ next.y, next.x, ncost });

				ny += diry[i];
				nx += dirx[i];
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << i << "와" << j << "까지의 최단 거리: " << dist[i][j] << "\n";
			}
		}

	}

	cout << "보석 위치" << dist[jewy][jewx];
}
/*
0(상),1(하) - 게이지 올리기, 땅이면 초기화.  
2(좌),3(우) - 땅이어야 좌우로 이동 가능.
limit과 cost?!
*/

int main() {

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 2) {
				snowy = i;
				snowx = j;
			}else if (MAP[i][j] == 3) {
				jewy = i;
				jewx = j;
			}
		}
	}

	dijkstra(snowy, snowx);
}
