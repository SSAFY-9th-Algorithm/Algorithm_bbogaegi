#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int parent[11];
int N;
int pp[11]; // 유권자 수
//int MAP[11][11]; // 마을의 연결 정보 저장
vector<int> al[11]; // 마을의 연결 정보 저장
int M; // 몇개로 선거구를 구성할 것인가
int ans;
int visited[11];

void INIT() {
	memset(pp, 0, sizeof(pp));
	//memset(MAP, 0, sizeof(MAP));
	memset(visited, 0, sizeof(visited));
	memset(parent, 0, sizeof(parent));
	memset(al, 0, sizeof(al));
	ans = 21e8;
}

void input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int num;
			cin >> num;
			if (num) 
				al[i].push_back(j);
				
		}
	}
	for (int i = 1; i <= N; i++)
		cin >> pp[i];
}

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
	if (A < B)
		parent[pb] = pa;
	else
		parent[pa] = pb;
}

bool isConnected(vector<int> v) {
	queue<int> q;
	q.push(v[0]);

	int used[11] = { 0, };
	used[v[0]] = 1;

	while (!q.empty())
	{
		int now = q.front();
		q.pop();

		for (int i = 0; i < al[now].size(); i++) {
			int next = al[now][i];
			if (used[next])
				continue;
			if (Find(next) != Find(now))
				continue;
			used[next] = 1;
			q.push(next);
		}
	}
	for (auto i : v)
		if (!used[i]) return false;
	return true;
}

void dfs(int now, int idx) {
	if (ans == 0)
		return;

	if (now == M) {
		vector<int> A, B;
		int Asum = 0, Bsum = 0;

		for (int i = 1; i <= N; i++)
			parent[i] = i;

		for (int i = 1; i <= N; i++) {
			if (visited[i]) {
				A.push_back(i);
				Asum += pp[i];
			}
			else {
				B.push_back(i);
				Bsum += pp[i];
			}
		}

		for (int i = 0; i < A.size() - 1; i++)
			Union(A[i], A[i + 1]);
		for (int i = 0; i < B.size() - 1; i++)
			Union(B[i], B[i + 1]);

		if (isConnected(A) && isConnected(B)) {
			if (ans > abs(Asum - Bsum))
				ans = abs(Asum - Bsum);
		}
		return;
	}
	for (int i = idx; i <= N; i++) {
		if (visited[i])
			continue;
		visited[i] = 1;
		dfs(now + 1, i + 1);
		visited[i] = 0;
	}
}

int main() {
	int T;
	cin >> T;
	for(int tc = 1;tc<=T;tc++) {
		//reset
		INIT();

		// input
		input();

		// solve
		for (int i = 1; i <= N / 2; i++) {
			memset(visited, 0, sizeof(visited));
			M = i;
			dfs(0, 1);
		}
		// output
		if (ans == 21e8) ans = -1;
		cout << '#' << tc << ' ' << ans << '\n';
	}
	return 0;
}
