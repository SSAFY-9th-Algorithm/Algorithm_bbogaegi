#include <iostream>
#include <cstring>
using namespace std;

int N, slist[4], num[12], path[11];
int MAX, MIN;

void dfs(int level) {
	if (level == N - 1) {
		int sum = num[0];
		for (int i = 0; i < N - 1; i++) {
			if (path[i] == 0)sum += num[i + 1];
			else if (path[i] == 1) sum -= num[i + 1];
			else if (path[i] == 2) sum *= num[i + 1];
			else { sum /= num[i + 1]; }
		}
		if (sum > MAX)MAX = sum;
		if (sum < MIN)MIN = sum;

		return;
	}

	for (int i = 0; i < 4; i++) {
		if (slist[i] == 0)continue;
		path[level] = i;
		slist[i]--;

		dfs(level + 1);
		path[level] = 0;
		slist[i]++;
	}
}


int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		sign = "";
		MAX = -21e8;
		MIN = 21e8;
		cin >> N;
		for (int i = 0; i < 4; i++) { cin >> slist[i]; }
		for (int i = 0; i < N; i++) { cin >> num[i]; }

		dfs(0);

		cout << "#" << tc << " " << MAX - MIN << "\n";

		memset(num, 0, sizeof(num));
		memset(path, 0, sizeof(path));
		memset(slist, 0, sizeof(slist));
	}

}
