// 최단비용으로 A->B로 가는거는 다익스트라 알고리즘 사용이라는걸 까먹음
// BFS로 허탕치다가 Dijkstra로 변경(노션참고 ㅎ)
// 멘탈나가서 하다가 세이코드 참고했음

// 전반적으로 어려운 것 없었고, 터널을 빨리 찾으려고 2차원 벡터 이용하긴 했는데
// 일반 벡터하나에 푸시백 다하고 포문으로 찾는게 좋은지 어떤게 좋은지는 잘 모르겠다.

// 너무쉬운 문제였다는걸 알고 화나서 자려고 함
// 이제 최단경로 문제 다익스트라 최경다익스트라 ..최다익..

// + ternel 이 아니고 tunnel 

#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;



struct Ternel {
	int ty, tx,cost;
};
struct Coord {
	int y, x;
	int cost;
	bool operator < (Coord next) const {
		if (cost < next.cost)
			return false;
		if (cost < next.cost)
			return true;
		return false;
	}
};

vector<Ternel> ternel[31][31];
int N, M, K[30], MAP[31][31], dist[31][31];

// 초기화 함수
void reset() {
	memset(MAP, 0, sizeof(MAP));
	memset(dist, 0, sizeof(dist));
	memset(ternel, 0, sizeof(ternel));
}

// 입력 함수
void input() {
	cin >> N >> M;
	// 맵 입력
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> MAP[i][j];
		}
	}
	// 터널 입력
	for (int i = 1; i <= M; i++) {
		int sy, sx, ey, ex,cost;
		cin >> sy >> sx >> ey >> ex>>cost;
		ternel[sy][sx].push_back({ ey,ex,cost });
		ternel[ey][ex].push_back({ sy,sx,cost });
	}
}

void dijkstra(int y, int x) {
	priority_queue < Coord>pq;
	pq.push({ y,x,0 });

	int ydir[] = { -1,1,0,0 };
	int xdir[] = { 0,0,-1,1 };

	// 초기값 세팅
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			dist[i][j] = 21e8;
		}
	}
	dist[y][x] = 0;


	while (!pq.empty()) {
		Coord now = pq.top();
		pq.pop();

		if (now.cost > dist[now.y][now.x])continue;

		// 터널인지 확인
		if (ternel[now.y][now.x].size() != 0) {
			for (int tt = 0; tt < ternel[now.y][now.x].size(); tt++) {
				int ny = ternel[now.y][now.x][tt].ty;
				int nx = ternel[now.y][now.x][tt].tx;
				int nowcost = now.cost + ternel[now.y][now.x][tt].cost;
				//cout << now.y << " , " << now.x << "번 터널에 들어왔다\n";
				if (dist[ny][nx] > nowcost) {
					dist[ny][nx] = nowcost;
					//cout << ny << " , " << nx << "번 터널로 나왔다\n";
					pq.push({ ny,nx,nowcost });
				}
			}
		}

		// 4방향 확인
		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			int nowcost;

			if (ny < 1 || nx <1 || ny > N || nx > N) continue;
			// 비용 정하기
			if (MAP[now.y][now.x] == MAP[ny][nx])nowcost = now.cost+1;
			else if (MAP[now.y][now.x] > MAP[ny][nx]) nowcost = now.cost;
			else nowcost = now.cost + abs(MAP[now.y][now.x] - MAP[ny][nx]) * 2;

			if (dist[ny][nx] <= nowcost) continue;
			dist[ny][nx] = nowcost;
			pq.push({ ny,nx,nowcost });

		}

	}
	//for (int i = 1; i <= N; i++) {
	//	for (int j = 1; j <= N; j++)
	//		cout << dist[i][j] << ' ';
	//	cout << '\n';
	//}
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
		dijkstra(1, 1);
		// output
		cout << "#" << tc << " " << dist[N][N] << '\n';
	}
}
