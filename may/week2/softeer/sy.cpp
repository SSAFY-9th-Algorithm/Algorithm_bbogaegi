#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <queue>
using namespace std;

vector<int> ord[20];
queue<int> task[1025];
int H, K, R;

void init() {
	ord[1] = { 2,1 };
	for (int i = 2; i <= H; i++) {
		int ed = ord[i - 1].size();
		for (int j = 0; j < ed; j++) {
			int val = 1 << (i - 1);
			if (i % 2 == 0) {
				ord[i].push_back(ord[i - 1][j]);
				ord[i].push_back(ord[i - 1][j] + val);
			}
			else {
				ord[i].push_back(ord[i - 1][j] + val);
				ord[i].push_back(ord[i - 1][j]);
			}
		}
	}
}

void input() {
	cin >> H >> K >> R;
	init();
	for (int i = 1; i <= (1 << H); i++) {
		for (int j = 0; j < K; j++) {
			int num;
			cin >> num;
			task[i].push(num);
		}
	}
}

void solve() {
	int res = 0;
	if (H >= R)
		cout << "0\n";
	else {
		int idx = 0;
		for (int t = H+1; t <= R; t++) {
			int now = ord[H][idx++];
			if (task[now].empty())
				break;
			res += task[now].front();
			task[now].pop();
		}
		cout << res << '\n';
	}
}

int main() {
	fastIO;
	input();
	solve();
	return 0;
}
