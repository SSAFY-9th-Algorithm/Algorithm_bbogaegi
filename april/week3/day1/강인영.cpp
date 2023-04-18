#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int MAP[51][51];
int N, M;

struct Building {
	int y;
	int x;
	int type; // 치킨집 2 , 집 1
};
vector<Building>chickens;
vector<Building>homes;
int picked[101];
int result = 21e8;

//거리 값을 리턴해주고 해당 값으로 도시의 치킨 거리 값 
int check(int num, int chickenNum) {
	int dist = abs(homes[num].y - chickens[chickenNum].y) + abs(homes[num].x - chickens[chickenNum].x);
	return dist;
}

//각 집에서 치킨집을 선택함
//선택한 치킨집의 개수가 M개가 넘어가면 return
//그 안에서 집이 치킨집을 잘 선택하면 picked에 저장된 치킨집 숫자를 가지고 거리 산출
void dfs(int level, int cnt) {

	if (cnt > M) {
		return;
	}

	if (level == homes.size()) {
		int totalsum = 0;
		for (int i = 0; i < homes.size(); i++) {
			//cout << picked[i] << ' ';
			totalsum += check(i, picked[i]-1);
		}
		//cout << endl;

		if (totalsum < result)
			result = totalsum;

		return;
	}
	
	for (int i = 1; i < chickens.size()+1; i++) {
		picked[level] = i;

		int flag = 0;
		for (int j = 0; j < level; j++) {
			if (picked[level] == picked[j])
				flag = 1;
		}
		if (!flag)
			cnt++;

		dfs(level + 1, cnt);

		if (!flag)
			cnt--;
		flag = 0;
		picked[level] = 0;
	}

}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 1) {
				homes.push_back({ j, i, 1 });
			}
			else if (MAP[i][j] == 2) {
				chickens.push_back({ i, j, 2 });
			}
		}
	}

	dfs(0, 0);
	cout << result;

}
