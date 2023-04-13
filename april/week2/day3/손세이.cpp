#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <queue>
using namespace std;
#define MAX 201

// 설계
// #1. 맵을 0,0 부터 200, 200까지 매핑
// #2. 맵에 기본 코스트 1을 주고
// #3. 지하철은 cost 0
// #4. dijkstra
// -> 더 좋은 방법이 있을거같은데 

struct Node {
	int y, x;
	int cost;
	bool operator < (Node next) const {
		return cost > next.cost;
	}
};

struct Pos {
	int y, x;
};

// 상 하 좌 우
int ydir[] = { 1,-1,0,0 };
int xdir[] = { 0,0,-1,1 };

int dist[MAX][MAX];
int MAP[MAX][MAX];
vector<Pos> v;
Pos path[MAX][MAX];

int sy, sx;
int dy, dx;
int mxy = -1, mxx = -1, miy = 201, mix = 201;
int ans;

void input() {
	cin >> sx >> sy;
	cin >> dx >> dy;
	sy += 100;
	sx += 100;
	dy += 100;
	dx += 100;

	
	for (int i = 0; i < 4; i++) {
		int y, x;
		cin >> x >> y;
		mxy = max(mxy, y + 100);
		mxx = max(mxx, x + 100);
		miy = min(miy, y + 100);
		mix = min(mix, x + 100);
	}
}

bool outRange(int y, int x) {
	return y < 0 || x < 0 || y >= MAX || x >= MAX;
}

void dijkstra(int y, int x) {
	priority_queue<Node> pq;
	pq.push({ y, x, 0 });

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++)
			dist[i][j] = 21e8;
	}
	dist[y][x] = 0;

	while (!pq.empty())
	{
		Node now = pq.top();
		pq.pop();
		if (now.cost > dist[now.y][now.x])
			continue;

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (outRange(ny, nx))
				continue;
			
			int ncost = now.cost + MAP[ny][nx];
			if (ncost >= dist[ny][nx])
				continue;

			path[ny][nx] = { now.y, now.x };
			dist[ny][nx] = ncost;
			pq.push({ ny, nx, ncost });
		}
	}
	
	ans = dist[dy][dx];
}

void makeCost() {
	for (int j = mix; j <= mxx; j++) {
		MAP[miy][j] = 0;
		MAP[mxy][j] = 0;
	}
	for (int i = miy; i <= mxy; i++) {
		MAP[i][mix] = 0;
		MAP[i][mxx] = 0;
	}
}

void getpath(int dy, int dx) {
	v.push_back({dy, dx});
	int ty = -1, tx = -1;
	while (!(dy == sy && dx == sx)) {
		v.push_back({ path[dy][dx] });
		ty = path[dy][dx].y, tx = path[dy][dx].x;
		dy = ty;
		dx = tx;
	}
}

int checkPos() {
	int flag = 0;
	if (((sy == miy || sy == mxy) && (sx >= mix && sx <= mxx)) || ((sx == mix || sx == mxx) && (sy >= miy && sy <= mxy)))
		flag = 1;
	
	if (((dy == miy || dy == mxy) && (dx >= mix && dx <= mxx)) || ((dx == mix || dx == mxx) && (dy >= miy && dy <= mxy)))
		flag = 1;
	
	if ((((sy == miy || sy == mxy) && (sx >= mix && sx <= mxx)) || ((sx == mix || sx == mxx) && (sy >= miy && sy <= mxy))) &&
		(((dy == miy || dy == mxy) && (dx >= mix && dx <= mxx)) || ((dx == mix || dx == mxx) && (dy >= miy && dy <= mxy))))
		flag = 2;
	return flag;
}

int solve() {
	input();
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++)
			MAP[i][j] = 1;
	}
	// 사각형 좌표에 대해 코스트를 처리 해보자
	int flag = checkPos();
	if (flag == 2)
		return 0;

	makeCost();
	dijkstra(sy, sx);
	// 만약 시작 좌표 or 도착좌표가 지하철 위에 있다면?
	if (flag == 1)
		return ans;
	
	getpath(dy, dx);
	for (int i = 0; i < v.size(); i++) {
		Pos now = v[i];
		if (now.y == miy || now.y == mxy) {
			if (now.x >= mix && now.x <= mxx) {
				ans++;
				break;
			}
		}
		else if (now.x == mix || now.x == mxx) {
			if (now.y >= miy && now.y <= mxy) {
				ans++;
				break;
			}
		}
	}
	return ans;

}

int main() {
	fastIO;
	int res = solve();
	cout << res << '\n';

	return 0;
}
