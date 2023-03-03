#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// �ִܰ�θ� ã�� ������ �ƴ϶� �����̵��� �����̴�
// ���� �̵� �������� ����ġ��� �����ϸ���
// bfs�� �̿��Ϸ��� �ôµ� 
// �������� ���� �ּ� ����ġ ã��
// ����ġ�� ���ͽ�Ʈ��?
// ����ġ ã�Ⱑ �����ʴ�

struct Node {
	int y;
	int x;
	int cost;

	bool operator < (Node next) const {
		return cost > next.cost;
	}
};


int N, M;
int MAP[50][50];
int sy, sx, ey, ex;

void dijkstra(int now) {
	priority_queue<Node>pq;
	pq.push({ sy, sx, 0 });

	int dy[4] = { -1, 1, 0, 0 };
	int dx[4] = { 0, 0, -1, 1 };

	int dist[50][50];
	int MAX = 21e8;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			dist[i][j] = MAX;

	dist[sy][sx] = 0;

	while (!pq.empty()) {
		Node now = pq.top();
		pq.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= M)
				continue;	// ��������� ���������� �ڵ带 �ƴµ�
			// ���� �ִ� ���� ���Ʒ�, �¿��ε� ���� ������ �ִ�
			// ���Ʒ� -> ���� ���������ϱ��� �̵�����
			// �¿� -> ���� �־�� ����


		}

	}
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			cin >> MAP[i][j];
		}
	}
}