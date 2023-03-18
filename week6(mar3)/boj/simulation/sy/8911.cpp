#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

/*
F: 한 눈금 앞으로
B: 한 눈금 뒤로
L: 왼쪽으로 90도 회전
R: 오른쪽으로 90도 회전
*/

int ydir[] = { 1,-1,0,0 };
int xdir[] = { 0,0,-1,1 };

int leftRotate[] = { 2,3,1,0 };
int rightRotate[] = { 3,2,0,1 };

int mxy, mxx, miy, mix;

string qry;

void INIT() {
	mxy = 0;
	mxx = 0;
	miy = 0;
	mix = 0;
	qry = "";
}

int solve(int len) {
	int res = 0;
	int x = 0, y = 0, dir = 0;
	for (int i = 0; i < len; i++) {
		char now = qry[i];

		// 앞으로 움직이기
		if (now == 'F') {
			y += ydir[dir];
			x += xdir[dir];
		}
		// 뒤로 움직이기
		else if (now == 'B') {
			y -= ydir[dir];
			x -= xdir[dir];
		}
		// 왼쪽 회전
		else if (now == 'L')
			dir = leftRotate[dir];
		// 오른쪽 회전
		else
			dir = rightRotate[dir];

		mxy = max(y, mxy);
		mxx = max(x, mxx);
		mix = min(x, mix);
		miy = min(y, miy);
	}
	res = (abs(mxx - mix)) * (abs(mxy - miy));
	if ((mxx == 0 && mix == 0)||(mxy == 0 && miy == 0))
		res = 0;
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// reset
		INIT();
		// input
		cin >> qry;
		int len = qry.length();
		// solve
		int res = solve(len);
		// output
		cout << res << '\n';
	}

	return 0;
}
