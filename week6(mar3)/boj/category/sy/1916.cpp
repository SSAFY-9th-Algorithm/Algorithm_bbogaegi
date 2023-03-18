#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int to;
	int cost;

	bool operator < (Node next) const {
		return cost > next.cost;
	}
};

int N, M;
int dist[1001];
vector<Node> al[1001];
int S, D;

void dijkstra(int start) {
	priority_queue<Node> pq;
	pq.push({ start, 0 });

	for (int i = 1; i <= N; i++)
		dist[i] = 21e8;

	dist[start] = 0;

	while (!pq.empty())
	{
		Node now = pq.top();
		pq.pop();

		if (now.cost > dist[now.to])
			continue;

		for (int i = 0; i < al[now.to].size(); i++) {
			int next = al[now.to][i].to;
			int ncost = now.cost + al[now.to][i].cost;

			if (ncost >= dist[next])
				continue;

			dist[next] = ncost;
			pq.push({ next, ncost });
		}
	}
	cout << dist[D];
}

int main() {
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int from, to, cost;
		cin >> from >> to >> cost;
		al[from].push_back({ to, cost });
		//al[to].push_back({ from, cost });
	}
	cin >> S >> D;
	dijkstra(S);

	return 0;
}
