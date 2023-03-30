#include <iostream>
#include <vector>
using namespace std;

struct NODE {
	int dest;
	int weight;
};

/*
	src: 출발지, dest: 목적지
	_max는 src, dest로 가는 경로 상에서 가장 가중치가 큰 간선의 가중치
	len은 src, dest로 가는 동안 거치는 모든 간선의 가중치 합
	_min은 len의 최소값(여러 경로 중 가장 짧은 경로)
*/

int N;
vector<NODE> MAP[100001];
int src, dest;
int path[100001];
int _max, len, _min = 21e8;

void dfs(int now) {
	if (now == dest) {
		if (len - _max < _min)
			_min = len - _max;
		return ;
	}
	for (int i = 0; i < MAP[now].size(); i++) {
		int temp = _max;
		NODE next = MAP[now][i];
		if (path[next.dest])
			continue;
		path[next.dest] = 1;
		_max = _max < next.weight ? next.weight : _max;
		len += next.weight;
		dfs(next.dest);
		len -= next.weight;
		_max = temp;
		path[next.dest] = 0;
	}
}

int main(void) {
	cin >> N >> src >> dest;
	for (int i = 0; i < N - 1; i++)
	{
		int s, d, w;
		cin >> s >> d >> w;
		MAP[s].push_back({d, w});
		MAP[d].push_back({s, w});
	}
	path[src] = 1;
	dfs(src);
	cout << _min;
	return 0;
}