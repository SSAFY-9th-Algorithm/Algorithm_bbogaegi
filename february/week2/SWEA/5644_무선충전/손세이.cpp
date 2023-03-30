#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

// 어려웠던 점
// 1. 처음에 생각을 잘못해서 두명이 같은 충전소에 있으면 반씩 나눠야한다고 생각했음
// 2. 충전소를 저장해서 하지 않고 그냥 매번 계산하다 망함


// 설계
// #1. 거리 구하기
// #2. 범위 내에 충전기가 있는지 확인 -> 있으면 저장
// #3. 저장한 충전기로 전체 충전량 구함
// #4. 이동 후 1~3 반복

struct BC {
	int y;
	int x;
	int c; // 충전 범위
	int p; // 성능 (얼만큼 충전할 수 있는가)
};

struct User {
	int y;
	int x;
};

// 1: 상 2: 우 3: 하 4: 좌
int ydir[5] = { 0, -1, 0, 1, 0 };
int xdir[5] = { 0, 0, 1, 0, -1 };

int M, bcCnt; // 총 이동시간, bc 개수
BC bc[9]; // bc 정보를 저장할 배열
vector<int>Abc, Bbc; // A, B의 범위 내에 있는 충전기를 담아 놓을 vector

// 거리 구하는 함수
int getDist(int x1, int x2, int y1, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

// 충전기 구하는 함수
void getBC(User A, User B) {
	for (int i = 0; i < bcCnt; i++) {
		BC now = bc[i];
		if (getDist(now.x, A.x, now.y, A.y) <= now.c)
			Abc.push_back(i);
		if (getDist(now.x, B.x, now.y, B.y) <= now.c) 
			Bbc.push_back(i);
	}
}

// 실제 충전 되는 양을 구하는 함수
int charge() {
	int res = 0;
	// A, B 모두 충전소가 있다면
	if (!Abc.empty() && !Bbc.empty()) {
		for (int A : Abc) {
			BC a = bc[A];
			for (int B : Bbc) {
				BC b = bc[B];
				// 같은 충전소에 두개가 있다면 -> 어차피 총량은 같기 때문에 그냥 총량만 더하면 됨
				if (A == B) res = max(res, a.p);
				else res = max(res, a.p + b.p); // 다른 충전소에 있다면 각 값을 더해서 계산
			}
		}
	}
	// A 만 있는 경우
	else if (!Abc.empty()) {
		for (int A : Abc) {
			BC a = bc[A];
			res = max(res, a.p);
		}
	}
	// B만 있는 경우
	else {
		for (int B : Bbc) {
			BC b = bc[B];
			res = max(res, b.p);
		}
	}
	return res;
}

int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		// reset
		int ans = 0; 
		memset(bc, 0, sizeof(bc));
		Abc.clear(), Bbc.clear();
		vector<int> A_move;
		vector<int> B_move;
		int Ax = 1, Ay = 1, Bx = 10, By = 10;

		// input
		cin >> M >> bcCnt;
		for (int i = 0; i < M; i++) {
			int a;
			cin >> a;
			A_move.push_back(a);
		}
		for (int i = 0; i < M; i++) {
			int b;
			cin >> b;
			B_move.push_back(b);
		}
		for (int i = 0; i < bcCnt; i++) {
			int x, y, c, p;
			cin >> x >> y >> c >> p;
			bc[i] = { y,x,c,p };
		}

		// solve
		// 첫 위치에 충전기가 있는지 확인
		getBC({ Ay, Ax }, { By ,Bx });
		ans += charge();

		// A, B를 이동시키며 충전
		for (int i = 0; i < M; i++) {
			Abc.clear(), Bbc.clear();
			int dirA = A_move[i], dirB = B_move[i];
			Ax += xdir[dirA], Ay += ydir[dirA];
			Bx += xdir[dirB], By += ydir[dirB];

			getBC({ Ay, Ax }, { By, Bx });
			ans += charge();
		}

		// output
		cout << "#" << tc << " " << ans << '\n';
	}

	return 0;
}
