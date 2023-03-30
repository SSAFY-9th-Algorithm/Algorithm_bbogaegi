#include <iostream>
#include <queue>
using namespace std;

struct tree {
	int y, x, age, isAlive;

	bool operator< (tree next)const {
		if (age < next.age) return false;
		if (age > next.age) return true;
		return false;
	}
};

priority_queue<tree> pq;
int A[11][11], MAP[11][11], N, M, K;


void input() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
		{
			cin >> A[i][j];
			MAP[i][j] = 5;
		}
	}

	for (int i = 0; i < M; i++) {
		int y, x, age;
		cin >> y >> x >> age;
		pq.push({ y,x,age,1 });
	}
}

priority_queue<tree> seasons(priority_queue<tree> pq) {
	priority_queue<tree> npq;
	int ydir[] = { -1,-1,-1,0,0,1,1,1 };
	int xdir[] = { -1,0,1,-1,1,-1,0,1 };
	int temp[11][11] = { 0, };

	while (!pq.empty()) {
		tree now = pq.top(); pq.pop();
		if (MAP[now.y][now.x] < now.age)
		{
			temp[now.y][now.x] += now.age / 2;
			continue;
		}

		else {
			MAP[now.y][now.x] -= now.age;
			now.age++;

			if (now.age % 5 == 0) {
				for (int i = 0; i < 8; i++) {
					int ny = now.y + ydir[i];
					int nx = now.x + xdir[i];
					if (ny<1 || nx<1 || ny>N || nx>N)continue;
					npq.push({ ny,nx,1,1 });
				}
			}
		}
		npq.push(now);
	}

	// 겨울
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			MAP[i][j] += A[i][j] + temp[i][j];

	return npq;
}

int main() {

	input();

	for (int i = 0; i < K; i++) pq = seasons(pq);
	cout << pq.size();
}
/*
10 1 1000
100 100 100 100 100 100 100 100 100 100
100 100 100 100 100 100 100 100 100 100
100 100 100 100 100 100 100 100 100 100
100 100 100 100 100 100 100 100 100 100
100 100 100 100 100 100 100 100 100 100
100 100 100 100 100 100 100 100 100 100
100 100 100 100 100 100 100 100 100 100
100 100 100 100 100 100 100 100 100 100
100 100 100 100 100 100 100 100 100 100
100 100 100 100 100 100 100 100 100 100
1 1 1
*/
