/*
- 사람 1 / 계단(소요시간) > 1
- 이동 시간(분) = | PR - SR | + | PC - SC |
계단 입구 도착 후 1분 뒤에 내려갈 수 있음
계단 위에는 동시에 최대 3명까지 수용 가능
계단 2개
*/

#include <iostream>
#include <vector>
using namespace std;

struct Person {
	int y;
	int x;
};
struct Stair {
	int y;
	int x;
	int value;
};

int n;
vector<Person>p;
vector<Stair>s;
int humanCnt;
vector<int> ready;
int ans;

int goDown(int stairNum) {
	Stair target = s[stairNum];

	int t;

	//계단 내려가기 코드 작성

	return t;
}

//각 사람 마다 어떤 계단을 갈지 조합 찾기
void dfs(int level) {
	if (level == humanCnt) {

		int stair1 = goDown(0);
		int stair2 = goDown(1);

		if (stair1 > stair2)
			ans = stair1;
		else
			ans = stair2;

		return;
	}

	for (int i = 0; i < 2; i++) {
		ready.push_back(i);
		dfs(level + 1);
		ready.pop_back();
	}

}

int main() {

	cin >> n;

	int tmp;
	for (int i = 0; i < n; i++) {
		for (int j = 0l j < n; j++) {
			cin >> tmp;
			if (cmp == 1)
				p.push_back({ i,j });
			else
				s.push_back({ i,j,cmp });
				
		}
	}

	humanCnt = p.size();
	dfs(0);

}
