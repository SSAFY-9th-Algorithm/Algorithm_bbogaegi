#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

// ������� (1, 1), ��������(N, N)���� ����

// ��������� ��ĭ�� ���� �ִ� ��� ��� Ȯ��
// ���µ� �Ҹ�Ǵ� ���� Ȯ�� & ��
// -> �� ���� ������ ����
// �ͳ��� ������������ �ٷ� ������ �������� ���ְ� ����� �־��� ������ ���



struct Node {
	int y;
	int x;
	int cost;

	bool operator < (Node next) const {
		if (cost > next.cost)
			return true;
		if (cost < next.cost)
			return false;
		return false;
	}
};

struct Tunnel {
	int Ty, Tx;
	int Tcost;
};

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

int N, M;	// M �ͳ� ����
int MAP[31][31];
vector<Tunnel> tunnel[31][31];
int dist[31][31];


// �ּ� ��� ���ϱ�
void func(int y, int x) {
	priority_queue<Node>pq;

	pq.push({ y, x, 0 });	// ���� ���
	
	
	int MAX = 21e8;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			dist[i][j] = MAX;	// dist�� �ִ밪�� �־���´� 

	dist[y][x] = 0;

	while (!pq.empty())
	{
		Node now = pq.top();
		pq.pop();

		if (now.cost > dist[now.y][now.x])
			continue;

		if (tunnel[now.y][now.x].size() != 0) {
			for (int i = 0; i < tunnel[now.y][now.x].size(); i++) {
				int ny = tunnel[now.y][now.x][i].Ty;
				int nx = tunnel[now.y][now.x][i].Tx;
				int nowcost = now.cost + tunnel[now.y][now.x][i].Tcost;
				
				if (dist[ny][nx] > nowcost) {
					dist[ny][nx] = nowcost;
					
					pq.push({ ny,nx,nowcost });
				}
			}
		}

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny <= 0 || nx <= 0 || ny > N || nx > N)
				continue;

			int newcost;

			if (MAP[now.y][now.x] > MAP[ny][nx]) // ��������
				newcost = now.cost;
			else if (MAP[now.y][now.x] < MAP[ny][nx]) { // ��������
				int add = MAP[ny][nx] - MAP[now.y][now.x];
				newcost = now.cost + (add * 2);
			}
			else // ����
				newcost = now.cost + 1;

			// �ͳ��� ��� ����? --> ó���� ���⼭ ������


			if (newcost >= dist[ny][nx])
				continue;
			dist[ny][nx] = newcost;
			pq.push({ ny, nx, newcost });
		}
	}
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		
		memset(MAP, 0, sizeof(MAP));
		memset(dist, 0, sizeof(dist));
		memset(tunnel, 0, sizeof(tunnel));
		
		cin >> N >> M;
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				cin >> MAP[i][j];

		for (int i = 0; i < M; i++) {
			int sy, sx, ey, ex, cost;
			cin >> sy >> sx >> ey >> ex >> cost;
			tunnel[sy][sx].push_back({ey, ex , cost});
			tunnel[ey][ex].push_back({ sy, sx , cost });
		}
		
		func(1, 1);
		
		cout << '#' << tc << ' ' << dist[N][N] << endl;
	}

	return 0;
}