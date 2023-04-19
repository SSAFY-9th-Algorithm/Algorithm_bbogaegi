#define _CRT_SECURE_NO_WARNINGS
#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <queue>
using namespace std;

// 설계
// 직접 돌리긴 싫으니 회전 부분 -> index 회전
// 로봇이 움직이는 부분 -> N번 반복하며 index를 이용하여 움직인다
// 로봇 올리기 -> 그냥 시작 인덱스에 올린다

int N, K;
int belt[201];
int robot[201];
int bcnt;
int flag;

void input() {
	cin >> N >> K;
	for (int i = 0; i < 2 * N; i++) {
		cin >> belt[i];
	}
}

void rotate(int& s, int& e) {
	// 벨트 회전
	if (s <= 0)
		s = 2 * N - 1;
	else
		s--;
	if (e <= 0)
		e = 2 * N - 1;
	else
		e--;
	
	if (robot[e])
		robot[e] = 0;
}

void MOVE(int s, int e) {
	int idx = e;
	for (int i = 0; i < N - 1; i++) {
    // 이동할 위치
		int next = idx;
    // 내 위치 -> idx
		if (!idx)
			idx = 2 * N - 1;
		else
			idx--;
    // 이동 가능하면 이동하자!
		if (!robot[next] && robot[idx] && belt[next] > 0) {
			belt[next]--;
      // 내구도가 0보다 작으면 고장 카운트 증가
			if (belt[next] <= 0) {
				bcnt++;
        
				if (bcnt >= K) {
					flag = 1;
					break;
				}
			}
      // 이동했다!
			robot[next] = 1;
			robot[idx] = 0;
		}
	}
	robot[e] = 0;
}

void MAKE(int s) {
  // 내구도가 있을때만 로봇을 
	if (belt[s]) {
		belt[s]--;
		// 내구도가 0보다 작으면 고장 카운트 증가
		if (belt[s] <= 0) {
			bcnt++;
			if (bcnt >= K) {
				flag = 1;
			}
		}
		robot[s] = 1;
	}
}

void solve() {
	int sidx = 0; // 로봇이 올라가는 index
	int didx = N - 1; // 하차하는 index
	int ord = 1;

	while (true)
	{
    // 회전
		rotate(sidx, didx);
    // 움직이자!
		MOVE(sidx, didx);
		// 로봇을 올리자
		MAKE(sidx);
    // 종료조건 -> 고장난 개수가 K이상
		if (flag)
			break;
    // 단계 증가
		ord++;
	}
	cout << ord << '\n';
}

int main() {
	fastIO;
	input();
	solve();
	return 0;
}
