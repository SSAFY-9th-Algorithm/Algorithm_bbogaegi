/*
1번 - 올리는 위치
N번 - 내리는 위치
로봇이 어떤 칸으로 이동하면 그 칸의 내구도 1 감소
건너편으로 옮기기
1. 벨트는 한 칸 회전
2. 가장 먼저 벨트에 오른 로봇부터 회전 방향대로 한 칸 이동. 만약 이동 불가라면, 가만히 있기
	이동하려는 칸에 로봇이 없고, 그 칸의 내구도가 1이상 남아 있으면 이동 가능
3. 올리는 위치에 칸 내구도가 0이 아니면 로봇 올리기
4. 내구도 0인 칸의 개수가 K개 이상이라면 과정 종료. 
*/
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int N, K;
struct Block {
	int val; //내구성
	int exitRobot; //없으면 0, 있으면 1
};
Block belt[201];
int robotCnt = 0;
queue<int>Robot;

int check() {
	int zeroBlock = 0;

	for (int i = 0; i < 2*N; i++) {
		if (belt[i].val == 0)
			zeroBlock++;
	}

	if (zeroBlock >= K)
		return 0;
	return 1;
}

int main() {
	cin >> N >> K;

	for (int i = 0; i < 2 * N; i++) {
		int value;
		cin >> value;
		belt[i] = { value, 0 };
	}

	cout << "입력belt" << endl;
	for (int i = 0; i < 2 * N; i++)
		cout << belt[i].val << ":" << belt[i].exitRobot << ' ';
	cout << endl;

	int round = 0;
	while (check() == 1) {
		round++;
		cout << "##### 라운드" << round << " ####" << endl;
		//돌리기
		Block last = belt[2 * N - 1];
		Block tmpbelt[201];
		memcpy(tmpbelt, belt, sizeof(tmpbelt)); 
		for (int i = 2 * N - 1; i >= 0 ; i--) {
			Block now = belt[i];
			belt[i + 1] = now;
		}
		belt[0] = last;
		if (belt[2 * N - 1].exitRobot == 1) {
			belt[2 * N - 1].exitRobot = 0;
		}
		for (int i = 0; i < 2 * N; i++)
			cout << belt[i].val << ":" << belt[i].exitRobot << ' ';
		cout << endl;

		if (!Robot.empty()) {
			int rs = Robot.size();
			for (int i = 0; i < rs; i++) {
				int robotLoc = Robot.front();
				Robot.pop();
				if (robotLoc < 2 * N - 2) {
					int newLoc = robotLoc + 1;
					if (newLoc >= 2 * N)
						newLoc %= (2 * N);
					Robot.push(newLoc);
				}
			}
		}

		int rsize = Robot.size();
		for (int i = 0; i < rsize; i++) {
			int robotLoc = Robot.front();
			Robot.pop();
			int moveBlock = robotLoc + 1;
			if (moveBlock >= 2 * N)
				moveBlock %= (2 * N);
				if (belt[moveBlock].exitRobot != 1 && belt[moveBlock].val > 0) {
					belt[robotLoc].exitRobot = 0;
					belt[moveBlock].exitRobot = 1;
					belt[moveBlock].val--;
					Robot.push(moveBlock);
				}
		}

		if (belt[0].val != 0 && belt[0].exitRobot != 1) {
			belt[0].exitRobot = 1;
			belt[0].val--;
			Robot.push(0);
		}

		cout << "-----로봇이동----" << endl;
		for (int i = 0; i < 2 * N; i++)
			cout << belt[i].val << ":" << belt[i].exitRobot << ' ';
		cout << endl;

	}

	cout << round;

	return 0;
}
