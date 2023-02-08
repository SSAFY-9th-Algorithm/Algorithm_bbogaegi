#include <iostream>
#include <vector>
using namespace std;
// 
int N,robot1, robot2;
int visited[100001];
int maxw = 0;
int sum = 0;

vector<pair<int,int>> v[100001];

void dfs(int start,int des) {

	if (start == des) {
		cout << sum - maxw;
		return;
		}
	
	for (int next = 0; next < v[start].size(); next++) {
		int to = v[start][next].first;
		int w = v[start][next].second;
		// 간적 있는 노드는 가지 말 것
		if (visited[to] == 1)continue;
		
		visited[to] = 1;
		sum += w;
		if (w > maxw) maxw = w;

		dfs(to,des);

		visited[to] = 0;
		sum -= w;
	}

}

int main() {
	int N, robot1, robot2;

	cin >> N >> robot1 >> robot2;

	for (int i = 0; i < N-1; i++) {
		int from, to,w;
		cin >> from >> to >> w;
		v[from].push_back({ to,w });
		v[to].push_back({ from,w });
	}

	visited[robot1] = 1;
	dfs(robot1,robot2);


}
