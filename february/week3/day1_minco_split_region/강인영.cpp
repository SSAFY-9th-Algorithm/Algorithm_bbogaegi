/*
1. 입력받기
2. 사람들로 그룹 만들기
3. 그룹 만들어진 사람들이 연결되어있는지 확인하기
4. 유권자수 구하기 -> 최소가 되는 값으로 업데이트
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int T;
int map[8][8];
vector<int>v[8];
int people[8];
vector<int> p;
int used[8];
int n;
string team;

void group(int level, int limit) {
	if (level == limit) {
		for (int i = 0; i < p.size(); i++) {
			cout << p[i] << " ";
		}cout << endl;
		
		if (p.size() == 1) {
			//나머지 녀석들만 확인
		}
		else {
			// 해당 조합과 나머지 조합도 확인
		}

		return;
	}

	for (int x=0; x < n; x++) {
		if (used[x] == 1) continue;
		if (level > 0 && x < p[level - 1]) continue;
		p.push_back(x);
		used[x] = 1;
		group(level + 1, limit);
		p.pop_back();
		used[x] = 0;
	}
}

void check(int person) {
	//그룹된 녀석들이 연결되었는지 확인
}

int main() {
	cin >> T;

	int t = 0;
	int ans = 0;


	while (t < T) {

		cin >> n;

		//마을 & 유권자 입력
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> map[i][j];
				if(map[i][j] == 1){
					v[i].push_back(j);
				}
			}
		}
		for (int i = 0; i < n; i++) {
			cin >> people[i];
		}

		// 4 : 1 & 3 / 2 & 2 
		// 5 : 1 & 4 / 2 & 3 
		// 6 : 1 & 5 / 2 & 4 / 3 & 3
		// 7 : 1 & 6 / 2 & 5 / 3 & 4
		// 8 : 1 & 7 / 2 & 6 / 3 & 5 / 4 & 4
		for (int i = 1; i <= n/2; i++) {
			group(0, i);
		}

		cout << "#" << t++ << " " << ans << endl;
	}
}
