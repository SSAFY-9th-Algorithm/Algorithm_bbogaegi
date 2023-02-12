
#include <iostream>
#include <cstring>
using namespace std;

int MIN;
int plan[13];
int price[4]; 

void dfs(int month, int cost) {
	if (month >= 12) {
		if (cost < MIN) MIN = cost;
		return;
	}
	if (plan[month + 1] == 0)
		dfs(month + 1, cost);
	else {
		dfs(month + 1, cost + price[0] * plan[month + 1]);
		dfs(month + 1, cost + price[1]);
		dfs(month + 3, cost + price[2]);
	}
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		//reset
		memset(plan, 0, sizeof(plan));
		memset(price, 0, sizeof(price));
		MIN = 21e8;
		//input
		for (int i = 0; i < 4; i++)
			cin >> price[i];
		for (int i = 1; i <= 12; i++)
			cin >> plan[i];
		//solve
		if (MIN > price[3]) 
			MIN = price[3];
		dfs(0, 0);
		//output
		cout << "#" << tc << " " << MIN << '\n';
	}
	return 0;
}
