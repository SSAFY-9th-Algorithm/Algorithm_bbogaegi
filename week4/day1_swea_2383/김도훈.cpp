#include <iostream>
#include <cmath>
using namespace std;

// 모든 사람이 내려가는 최단 시간을 구하는 문제
// 계단까지 가는데 걸리는 시간 => |Y - Y| + |X - X|
// 계단에는 최대 3명까지만 가능
// 대기시간도 생각해줘야 하는구나...

// 계단 입구는 반드시 2개
// 사람들을 어느 계단을 이용하게 될지 두 그룸으로 먼저 나누기
// 근데 무조건 최단 거리를 기준으로 나누는게 이득인가?
// 한 계단에 몰리면 어차피 3명밖에 못가니까 대기를 해야하는데 
// 결국 모든 경우를 다봐야하는 거같으니까 DFS로 접근

// 모든 사람들이 계단을 어떻게 고르는지 모든 경우를 봐야한다.
// 1번 사람이 -> 1번 계단을 고르는 경우 -> 2번 사람이 -> 1번 계단을 고르는 경우
//			                           -> 2번 계단을 고르는 경우
//	     -> 2번 계단을 고르는 경우 -> 2번 사람이 -> 1번 계단을 고르는 경우
//			                           -> 2번 계단을 고르는 경우

// 2개의 구조체가 있으면 좋을 것 같다 -> 사람의 정보를 담은 구조체
//				    -> 계단의 정보를 담은 구조체

struct Person {
	int y;
	int x;
	int stairTime; // 계단까지 걸리는 시간
};

struct Stair {
	int y;
	int x;
	int leng;	// 계단의 길이
	int num;	// 계단에 존재하는 사람의 수 (3명이상은 안되기 때문)
};

int N;
int MAP[10][10];
int visited[10];
Person P[10];
Stair S[20];
int select[10];
int pNum;

int Dist(int people, int stairs) {	// 계단과 거리를 구하주는 함수
	int dy = abs(P[people].y - S[stairs].y);
	int dx = abs(P[people].x - S[stairs].x);

	return (dy + dx) + 1;	// 도착 후 1분 뒤에 내려가기 시작하기 때문에 1분을 더해줘봤다.
}

void gogo() {	//계단을 내려가는 모든 과정
	// 사람마다 계단에 도착하는 시간을 저장해줘야 한다
	// 저장을 구조체에 새로운 변수를 만들어서 그 사람의 걸린 시간을 저장할 수 있겠다.
	for (int i = 0; i < pNum; i++) {
		P[i].stairTime = Dist(i, select[i]);
		// i: i번째 사람 / select[i]: i번째 사람이 고른 계단
	}

	// ***여기서 뇌정지 와버림
	// 누구는 계단까지 가고 있고 누구는 내려가고...


}

void dfs(int level) {		// 모든 사람들이 계단을 고르는 모든 경우
	
	// 기저 조건 => 모든 사람이 계단 선택을 완료했을 때
	if (level == pNum) {
		// 선택이 끝났으면 시간을 구하는 과정 진행
		// 함수로 빼서 해보자
		gogo();
	}

	for (int i = 0; i < 2; i++) {
		select[level] = i;
		dfs(level + 1);
	}

}

int main() {

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {

		// reset


		cin >> N;
		for (int i = 0; i < 50; i++)
			for (int j = 0; j < 50; j++)
				cin >> MAP[i][j];

	}
}
