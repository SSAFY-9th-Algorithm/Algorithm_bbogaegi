#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
	int a, b;
	int cost;

	bool operator < (Edge next) const{
		return cost < next.cost;
	}
};

int V,E;
int parent[10001];
vector<Edge> al;

int Find(int now) {
	if (now == parent[now])
		return now;
	return parent[now] = Find(parent[now]);
}

void Union(int A, int B) {
	int pa = Find(A);
	int pb = Find(B);

	if (pa == pb)
		return;

	parent[pb] = pa;
}

int kruskal() {
	int sum = 0;
	int cnt = 0;
	sort(al.begin(), al.end());

	for (int i = 0; i < al.size(); i++) {
		Edge now = al[i];

		if (Find(now.a) == Find(now.b))
			continue;
		cnt++;
		Union(now.a, now.b);
		sum += now.cost;
	}
	if (cnt != V - 1)
		return -1;
	return sum;
}

int main() {
	cin >> V >> E;
	for (int i = 1; i <= V; i++)
		parent[i] = i;
	for (int i = 0; i < E; i++) {
		int a, b, cost;
		cin >> a >> b >> cost;
		al.push_back({ a,b,cost });
	}
	cout << kruskal();
	return 0;
}
