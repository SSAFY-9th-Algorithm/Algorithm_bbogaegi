#include <iostream>
#include <vector>
using namespace std;


// 0 1 2 3 -> 동 서 남 북
// 밀 수 있는 조합을 먼저 생각
// 00000, 00001, 00002, 00003, 00010 ... 모든경우를 생각해줘야한다
// -> dfs 이용


int N;
int MAP[21][21];
int tmp[21][21];
int tmpMAP[20][20];
int arr[5];
int ans = -21e8;
vector<int>v;

void move(int num) { // 방향이 정해지면 움직이게 하는 함수
	// 맵을 탐색하면서 0이 아니면 일단 벡터에 넣는다
	// 벡터를 탐색하면서 연속된 두 수가 같으면 2를 곱해서 맵을 채워준다

	if (num == 0) {	// 오른쪽으로 미는 경우
		// 오른쪽으로 미니까 행별로 오른쪽에서 왼쪽으로 탐색
		for (int i = 0; i < N; i++) {
			for (int j = N - 1; j >= 0; j--) {
				if (tmp[i][j] != 0) {
					v.push_back(tmp[i][j]);
				}
				tmp[i][j] = 0;
			}
			int idx = N - 1;
			for (int j = 0; j < v.size(); j++) {
				if (j + 1 < v.size() && v[j] == v[j + 1]) {
					tmp[i][idx] = v[j] * 2;
					j++;	// 같아서 더해준 다음에 더해진 수를 다시 보지않기 위해
				}
				else {
					tmp[i][idx] = v[j];
				}
				idx--;
			}
			v.clear();
		}
	}
	else if (num == 1) {	// 왼쪽으로 미는 경우
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (tmp[i][j] != 0) v.push_back(tmp[i][j]); // 처음부터 돌면서 벡터에 일단 다 넣어준다.
				tmp[i][j] = 0; // 넣어주면서 맵은 초기화
			}
			int idx = 0;
			for (int j = 0; j < v.size(); j++) { // 벡터를 처음부터 끝까지 돌면서
				if (j + 1 < v.size() && v[j] == v[j + 1]) {
					tmp[i][idx] = v[j] * 2;
					j++;
				}
				else tmp[i][idx] = v[j]; // 다르다면 그냥 현재 벡터값을 맵에 넣어준다.
				idx++;
			}
			v.clear();
		}
	}
	else if (num == 2) {	// 아래로 미는 경우
		for (int i = 0; i < N; i++) {
			for (int j = N - 1; j >= 0; j--) {
				if (tmp[j][i] != 0) v.push_back(tmp[j][i]);
				tmp[j][i] = 0;
			}
			int idx = N - 1;
			for (int j = 0; j < v.size(); j++) {
				if (j + 1 < v.size() && v[j] == v[j + 1]) {
					tmp[idx][i] = v[j] * 2;
					j++;
				}
				else tmp[idx][i] = v[j];
				idx--;
			}
			v.clear();
		}
	}
	else {	// 위로 미는 경우
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (tmp[j][i] != 0) v.push_back(tmp[j][i]);
				tmp[j][i] = 0;
			}
			int idx = 0;
			for (int j = 0; j < v.size(); j++) {
				if (j + 1 < v.size() && v[j] == v[j + 1]) {
					tmp[idx][i] = v[j] * 2;
					j++;
				}
				else tmp[idx][i] = v[j];
				idx++;
			}
			v.clear();
		}
	}
}


void dfs(int level) {
	if (level == 5) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				tmp[i][j] = MAP[i][j];

		
		for (int i = 0; i < 5; i++)
			move(arr[i]);
			//cout << arr[i];
		//cout << endl;

		/*for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << tmp[i][j] << " ";
			}
			cout << endl;
		}*/


		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				if (ans < tmp[i][j])
					ans = tmp[i][j];
			}
		return;
	}

	// 여기서 움직여주면 된다.
	/*for (int i = 0; i < 4; i++)
		move(arr[i]);*/


	for (int i = 0; i < 4; i++) {	// 움직일 수 있는 모든 경우
		arr[level] = i;
		dfs(level + 1);
		
	}
}


int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> MAP[i][j];
	dfs(0);
	cout << ans;
}