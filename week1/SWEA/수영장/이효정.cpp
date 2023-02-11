#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

int price[4];
int days[13];
int total, minTotal;

void dfs(int level) {
	if (level > 12) {
		if (total < minTotal) {
			minTotal = total;
		}
		return;
	}
	for (int i = 0; i < 3; i++) {
		int temp;
		if (days[level] < 1) {
			dfs(level + 1);
		}
		else if (i == 0) {
			temp = price[0] * days[level];
			total += temp;
			dfs(level + 1);
			total -= temp;
		}
		else if (i == 1) {
			temp = price[1];
			total += temp;
			dfs(level + 1);
			total -= temp;
		}
		else if (i == 2) {
			temp = price[2];
			total += temp;
			dfs(level + 3);
			total -= temp;
		}
	}
}

int main(void) {
	// freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> price[0] >> price[1] >> price[2] >> price[3];
		total = 0;
		minTotal = price[3];
		memset(days, 0, sizeof(days));
		for (int i = 1; i < 13; i++)
			cin >> days[i];
		dfs(1);
		cout << "#" << tc << " " << minTotal << '\n';
	}
}