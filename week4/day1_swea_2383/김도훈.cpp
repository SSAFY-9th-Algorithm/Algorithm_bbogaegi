#include <iostream>
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

// 문제 이해는 한 것같은데 시작이 쉽지않은..,, 시험 끝나면 좀더 고민해볼게요ㅠㅜ

struct Node {
	int y;
	int x;
};

int N;
int MAP[10][10];
int visited[10];

void dfs(int now) {

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