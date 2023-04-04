#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/* 코드트리 빵
m명의 사람. 1번 사람은 정확히 1분에, 2번 사람은 정확히 2분에, ..., m번 사람은 정확히 m 분에 각자의 베이스캠프에서 출발하여 편의점으로 이동.
목표 편의점이 모두 다름. n*n 격자
1. 본인이 가고 싶은 편의점 방향 향해서 1 칸. 최단 거리  ↑, ←, →, ↓ 의 우선 순위. 최단거리라 함은 상하좌우 인접한 칸 중 이동가능한 칸으로만 이동하여 도달하기까지 거쳐야 하는 칸의 수가 최소가 되는 거리
2. 편의점 도착 후 멈춤. 다른 사람들은 해당 편의점이 있는 칸을 지나갈 수 없음.
3. 현재 시간이 t분이고 t ≤ m를 만족한다면, t번 사람은 자신이 가고 싶은 편의점과 가장 가까이 있는 베이스 캠프에 들어감.
가장 가까운 베이스캠프가 여러 가지인 경우에는 그 중 행이 작은 베이스캠프, 행이 같다면 열이 작은 베이스 캠프
t번 사람이 베이스 캠프 이동하는 데 시간 소요 X
*/

int n, m;
int MAP[16][16];
int visited[16][16];
struct Block {
	int y;
	int x;
};
int diry[4] = { -1, 0, 0, 1 };
int dirx[4] = { 0, -1, 1, 0};
vector<Block>v;
vector<Block> people[31];

Block findCamp(int nowman) {
	
	Block conv = v[nowman - 1];
	Block nowCamp;
	queue<Block>q;
	q.push(conv);

	int flag = 0;
	while (!q.empty()) {

		if (flag == 1)
			break;

		int cursize = q.size();
		for (int c = 0; c < cursize; c++) {
			
			if (flag == 1)
				break;

			Block block = q.front();
			q.pop();

			for (int i = 0; i < 4; i++) {
				int ny = block.y + diry[i];
				int nx = block.x + dirx[i];

				if (ny < 0 || nx < 0 || ny >= n || nx >= n)
					continue;

				if (MAP[ny][nx] == 1 && MAP[ny][nx] != 3) {
					nowCamp = { ny, nx };
					flag = 1;
					break;
				}

				if (MAP[ny][nx] == 3)
					continue;

				q.push({ ny, nx });
			}
		}
	}

	return nowCamp;

}

int goConv(Block nowloc, Block manconv) {

	int tmpMAP[16][16] = {0, };
	queue<Block>qb;
	qb.push(manconv);
	tmpMAP[manconv.y][manconv.x] = 1;
	int flag = 0;

	while (!qb.empty()) {

		if (flag == 1)
			break;

		Block now = qb.front();
		qb.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + diry[i];
			int nx = now.x + dirx[i];

			if (ny < 0 || nx < 0 || ny >= n || nx >= n)
				continue;
			if (tmpMAP[ny][nx] != 0)
				continue;

			if (ny == nowloc.y && nx == nowloc.x) {
				tmpMAP[ny][nx] = tmpMAP[now.y][now.x] + 1;
				flag = 1;
				break;
			}

			if (MAP[ny][nx] == 3)
				continue;

			tmpMAP[ny][nx] = tmpMAP[now.y][now.x] + 1;			

			qb.push({ ny, nx });
		}
	}

	int movedir = -1;
	for (int i = 0; i < 4; i++) {
		int ny = nowloc.y + diry[i];
		int nx = nowloc.x + dirx[i];

		if (ny < 0 || nx < 0 || ny >= n || nx >= n)
			continue;

		if (tmpMAP[ny][nx] == tmpMAP[nowloc.y][nowloc.x] - 1) {
			movedir = i;
			break;
		}
	}

	if (movedir == -1)
		cout << -1 << '\n';

	return movedir;
}

int main() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> MAP[i][j];
		}
	}
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> y >> x;
		MAP[y-1][x-1] = 2;
		v.push_back({ y - 1, x - 1 });
	}

	int t = 1;
	while (1) {

		//1번
		for (int m = 1; m <= t; m++) {

			if (!people[m].empty()){
				int nowman = m;
				//현위치
				Block nowloc = people[m][0];
				//가야하는 편의점 위치
				Block manconv = v[m - 1];
				//갈 방향을 확정해서 이동할 위치
				int movedir = goConv(nowloc, manconv);

				people[m].clear();
				people[m].push_back({ nowloc.y+diry[movedir],  nowloc.x + dirx[movedir] });

				if (nowloc.y + diry[movedir] == manconv.y && nowloc.x + dirx[movedir] == manconv.x) {
					MAP[manconv.y][manconv.x] = 3;
					people[m].clear();
				}
			}
		}

		if (t <= m) {
			//3번
			int nowman = t;

			Block nowCamp = findCamp(nowman);
			MAP[nowCamp.y][nowCamp.x] = 3;
			people[nowman].push_back(nowCamp);
		}

		int stopflag = 0;
		for (int k = 1; k <= m; k++) {
			if (people[k].empty()) 
				stopflag++;
		}

		if (stopflag == m) {
			cout << t;
			return 0;
		}

		t++;

	}

}
